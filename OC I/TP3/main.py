# Ariel A. Santos - September 2021
# CC Licensed
import re
from dataclasses import dataclass
from sys import stdin
from typing import Optional, List, Tuple, Dict


class MemoryData:
    def __init__(self):
        self.data = {}

    @staticmethod
    def parse_address(address: str) -> int:
        return int(address, 2)

    def read(self, address: str) -> str:
        index = self.parse_address(address)
        if index in self.data:
            return self.data[index]
        return ''.zfill(32)

    def write(self, address: str, data: str):
        index = self.parse_address(address)
        self.data[index] = data


class MemoryCache:
    BLOCK_BYTES = 16
    WORD_BYTES = 4

    @dataclass
    class Block:
        dirty: bool
        tag: str
        data: str

    def __init__(self):
        self.main = MemoryData()
        self.cache: Dict[int, MemoryCache.Block] = {}
        self.address_pattern = re.compile(r'(\d{22})(\d{6})(\d{4})')

    def parse_address(self, address: str) -> Tuple[str, int, int]:
        tag, index, offset = self.address_pattern.search(address).groups()
        return tag, int(index, 2), int(offset, 2)

    def read(self, address: str) -> Tuple[bool, Optional[str]]:
        tag, index, offset = self.parse_address(address)

        if index in self.cache and self.cache[index].tag == tag:
            return False, self.cache[index].data[offset:offset - self.BLOCK_BYTES + self.WORD_BYTES]

        data = self.main.read(address)
        self.write(address, data)
        return True, data

    def write(self, address: str, data: str):
        tag, index, offset = self.parse_address(address)

        if index in self.cache and self.cache[index].dirty:
            self.main.write(address, data)

        new_block = MemoryCache.Block(tag=tag, dirty=True, data=data)
        self.cache[index] = new_block


class Memory:
    def __init__(self):
        self.cache = MemoryCache()

        self.read_counter = 0
        self.write_counter = 0
        self.hit_counter = 0
        self.miss_counter = 0

        self.cmd_pattern = re.compile(r'(\d{1,4}) (\d) ?(\d{32})?')
        self.cmd_history: List[str] = []

    def process_command(self, command: str):
        address, opt, data = self.cmd_pattern.search(command).groups()
        if address is None or opt is None:
            return
        address = bin(int(address))[2:].zfill(32)

        if opt == '0':
            self.read(address)
        else:
            self.write(address, data)

    def read(self, address: str):
        self.read_counter += 1
        miss, _ = self.cache.read(address)
        if not miss:
            self.miss_counter += 1
            self.cmd_history.append(f'{int(address, 2)} 0 H')
        else:
            self.hit_counter += 1
            self.cmd_history.append(f'{int(address, 2)} 0 M')

    def write(self, address: str, data: str):
        self.cache.write(address, data)
        self.write_counter += 1
        self.cmd_history.append(f'{int(address, 2)} 1 {data} W')

    def report(self) -> str:
        return (
                   f'READS: {self.read_counter}\n'
                   f'WRITES: {self.write_counter}\n'
                   f'HITS: {self.hit_counter}\n'
                   f'MISSES: {self.miss_counter}\n'
                   f'HIT RATE: {self.hit_counter / self.read_counter}\n'
                   f'MISS RATE: {self.miss_counter / self.read_counter}\n'
                   '\n'
               ) + '\n'.join(self.cmd_history)


if __name__ == '__main__':
    memory = Memory()
    for line in stdin:
        memory.process_command(line)
    print(memory.report(), end='')
