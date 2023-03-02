#!/usr/bin/env python3
"""Read nanobench formatted  timing data from stdin and write a TSV file
to stdout.

Call this script as

    xform.py < IN_FILENAME > OUT_FILENAME
"""
import sys
import locale
from typing import IO, Generator, List

# We want to use the C locale for parsing floating point numbers.
locale.setlocale(locale.LC_ALL, '')

class Block:
    """A Block represents the data from a single benchmark program run."""

    def __init__(self, start_line):
        """Initialize a new Block object."""
        self.entries = []
        self.name = make_name(start_line)
        self.headers: List[str] = []

    def print_header(self, outfile: IO, errfile: IO) -> None:
        """Write the header for this block to outfile.

        If there is no header, write an error message to errfile."""
        if not self.headers:
            errfile.write("Attempt to print header for a Block with no header")
            return
        outfile.write("\t".join(self.headers))

    def to_tsv(self) -> str:
        """Return the contained data as a tab-separated-value text.

        The text will contain one line for each entry."""
        return "\n".join(self.entries)

    def write_tsv(self, outfile: IO, _: IO) -> None:
        """Print this Block's data in tab-separated-value format."""
        outfile.write(self.to_tsv())

    def parse_data(self, text: str) -> None:
        """Parse a line of data."""
        parts = text.split("|")
        parts = parts[1:]



def make_name(text: str) -> str:
    """Transform the given text, which much be a compier-spec line, into the
    compiler name.
    """
    assert text.startswith("build-")
    return text[6:-1].replace("-", "_")


def is_compiler_line(text: str) -> bool:
    """Return True if the line is a header line."""
    return text.startswith("build")


def parse_header_line(text: str) -> List[str]:
    """Try to parse the line as a header line.

    If it is a header line, return a non-emtpy list of the header names.
    Return an empty list if this is not a header line.
    """
    if not text.startswith("|"):
        return []
    parts = [s.strip() for s in text.split("|")]
    if parts[1] == "ns/op":
        return parts[1:]
    return []


def parse_float(text: str) -> Optional[float]:
    """Parse the given string, using the C locale (and possibly removing a %) into a
    float. If the parsing fails, return None.
    """
    text = text.strip()
    if text.endswith("%"):
        return parse_float(text[:-1]) / 100.0
    try:
        number = locale.atof(text)
        return number
    except ValueError:
        return None



def gen_blocks(infile: IO) -> Generator[Block, None, None]:
    """Read blocks of timing data from infile.

    A block has the form:
        BLOCK-NAME
        <header line>
        <separator line>
        | NS-OP | OP-SEC | ERR% | TOTAL | LINE-NAME

    The last line is repeated an arbitrary number of times. The output
    """
    current_block = None  # we do not yet have a block
    for line in infile:
        line = line.strip()
        # skip blank lines and divider lines
        if not line or line.isspace() or line.startswith("|---"):
            continue

        # if we hit a new block, yield the old one if we have one
        if is_compiler_line(line):
            if current_block:
                yield current_block
            current_block = Block(line)
            continue

        # At this point we must have a current_block
        assert current_block is not None

        if headers := parse_header_line(line):
            current_block.headers = headers
            continue

        # the only other type of line is a data line
        current_block.parse_data(line)


def process_file(infile: IO, outfile: IO, errfile: IO) -> None:
    """Read lines from infile, and write tab-separated data to outfile. Errors
    are written to errfile.
    """
    # Create the generator
    blocks = gen_blocks(infile)
    first_block = next(blocks)
    first_block.print_header(outfile, errfile)

    for block in blocks:
        block.write_tsv(outfile, errfile)


if __name__ == "__main__":
    if len(sys.argv) != 1:
        print(__doc__)
        sys.exit(1)
    process_file(sys.stdin, sys.stdout, sys.stderr)
