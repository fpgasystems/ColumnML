-------------------------------------------------------------------------
--MIT License

--Copyright (c) 2018 FPGA @ Systems Group, ETH Zurich

--Permission is hereby granted, free of charge, to any person obtaining a copy
--of this software and associated documentation files (the "Software"), to deal
--in the Software without restriction, including without limitation the rights
--to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
--copies of the Software, and to permit persons to whom the Software is
--furnished to do so, subject to the following conditions:

--The above copyright notice and this permission notice shall be included in all
--copies or substantial portions of the Software.

--THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
--IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
--FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
--AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
--LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
--OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
--SOFTWARE.
----------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity AESDEC is
generic (
	LAST : integer := 0);
port (
	clk : in std_logic;

	in_valid : in std_logic;
	in_data : in std_logic_vector(127 downto 0);
	in_key : in std_logic_vector(127 downto 0);
	out_valid : out std_logic;
	out_data : out std_logic_vector(127 downto 0));
end AESDEC;

architecture structural of AESDEC is

signal InvShiftRows_valid : std_logic;
signal InvShiftRows_data : std_logic_vector(127 downto 0);

signal InvSubBytes_valid : std_logic;
signal InvSubBytes_data : std_logic_vector(127 downto 0);

signal InvMixColumns_valid : std_logic;
signal InvMixColumns_data : std_logic_vector(127 downto 0);

component InvShiftRows
port (
	clk : in std_logic;

	in_valid : in std_logic;
	in_data : in std_logic_vector(127 downto 0);
	out_valid : out std_logic;
	out_data : out std_logic_vector(127 downto 0));
end component;

component InvSubBytes
port (
	clk : in std_logic;

	in_valid : in std_logic;
	in_data : in std_logic_vector(127 downto 0);
	out_valid : out std_logic;
	out_data : out std_logic_vector(127 downto 0));
end component;

component InvMixColumns
port (
	clk : in std_logic;

	in_valid : in std_logic;
	in_data : in std_logic_vector(127 downto 0);
	out_valid : out std_logic;
	out_data : out std_logic_vector(127 downto 0));
end component;

begin

InvShiftRows_inst: InvShiftRows
port map (
	clk => clk,

	in_valid => in_valid,
	in_data => in_data,
	out_valid => InvShiftRows_valid,
	out_data => InvShiftRows_data);

InvSubBytes_inst: InvSubBytes
port map (
	clk => clk,

	in_valid => InvShiftRows_valid,
	in_data => InvShiftRows_data,
	out_valid => InvSubBytes_valid,
	out_data => InvSubBytes_data);

LAST_0: if LAST = 0 generate
	InvMixColumns_inst: InvMixColumns
	port map (
		clk => clk,

		in_valid => InvSubBytes_valid,
		in_data => InvSubBytes_data,
		out_valid => InvMixColumns_valid,
		out_data => InvMixColumns_data);
	process(clk)
	begin
	if clk'event and clk = '1' then
		out_valid <= InvMixColumns_valid;
		out_data <= InvMixColumns_data xor in_key;
	end if;
	end process;
end generate;
LAST_1: if LAST = 1 generate
	process(clk)
	begin
	if clk'event and clk = '1' then
		out_valid <= InvSubBytes_valid;
		out_data <= InvSubBytes_data xor in_key;
	end if;
	end process;
end generate;

end architecture;