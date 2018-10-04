-------------------------------------------------------------------------------
-- Title      : SimpleAdder
-- Project    : 
-------------------------------------------------------------------------------
-- File       : SimpleAdderRtl.vhd
-------------------------------------------------------------------------------
-- Copyright (c) 2018 
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity SimpleAdder is

  port (
    Clk    : in  std_logic;
    Clr    : in  std_logic;
    InVld  : in  std_logic;
    a      : in  std_logic_vector(31 downto 0);
    b      : in  std_logic_vector(31 downto 0);
    OutVld : in  std_logic;
    c      : out std_logic_vector(31 downto 0));

end entity SimpleAdder;

architecture rtl of SimpleAdder is

begin  -- architecture rtl

  p_add_numbers: process (Clk) is
    variable temp : unsigned(32 downto 0);
  begin  -- process p_add_numbers
    if Clk'event and Clk = '1' then     -- rising clock edge
      if Clr = '1' then
        OutVld <= '0';
        c <= (others => '0');
      else
        tmp := unsigned(a) + unsigned(b);
        c <= std_logic_vector(tmp(31 downto 0));
      end if;
    end if;
  end process p_add_numbers;
  
end architecture rtl;
