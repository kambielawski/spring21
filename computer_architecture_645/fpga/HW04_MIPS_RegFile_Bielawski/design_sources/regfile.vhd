LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;
USE work.my_package.ALL;

ENTITY RegFile IS
   PORT( 
      RA1      : IN  std_logic_vector (n_bits_of(reg_file_depth) - 1 DOWNTO 0);
      RA2 	   : IN  std_logic_vector (n_bits_of(reg_file_depth) - 1 DOWNTO 0);
      RegWrite : IN  std_logic;
      WA  	   : IN  std_logic_vector (n_bits_of(reg_file_depth) - 1 DOWNTO 0);
      WD  	   : IN  std_logic_vector (reg_file_width - 1 DOWNTO 0);
      clk      : IN  std_logic;
      rst      : IN  std_logic;
      RD1 	   : OUT std_logic_vector (reg_file_width - 1 DOWNTO 0);
      RD2 	   : OUT std_logic_vector (reg_file_width - 1 DOWNTO 0)
   );
END RegFile;

ARCHITECTURE behav OF RegFile IS

   -- Internal signal declarations
   SIGNAL reg_file  : mem_type(0 to reg_file_depth - 1);

BEGIN

   -- **************************** --
   -- DO NOT MODIFY or CHANGE the ---
   -- code template provided above --
   -- **************************** --
   
   -- ** INPUTS **
   -- RA1, RA2 <=> Register Address 1,2           [0:4]
   -- RegWrite <=> Enable writing to a register   [0]
   -- WA       <=> write register address         [0:1]
   -- WD       <=> write register data            [0:31]
   -- clk      <=> clock                          [0]
   -- rst      <=> asynchronous reset             [0]
   
   -- ** OUTPUTS **
   -- RD1, RD2 <=> register data from registers RA1, RA2   [0:31]
   
   -- reg_file <=> a length 23 array of 32-bit registers indexed by 0-22
   
   ----- insert your code here ------

    -- WritePort
    PROCESS (RegWrite, WA, WD, clk, rst)
        -- declare demuxed number
        VARIABLE addr : natural;
    BEGIN
        -- convert WA to natural
        addr := to_integer(unsigned(WA));
 
        if (clk = '1') then
 
            -- reset reg_file
            if (rst = '1') then
                reg_file <= (others => (others => '0'));
            -- otherwise write to reg_file if RegWrite = 1
            elsif (addr > 0 and addr < 23 and RegWrite = '1') then
                reg_file(addr) <= WD;
            end if;
             
        end if;

    END PROCESS;
    
    -- ReadPort1
    PROCESS (reg_file, RA1)
        variable addr : natural;
    BEGIN
        addr := to_integer(unsigned(RA1));
        if (addr < 23) then
            RD1 <= reg_file(addr);
        else
            RD1 <= (OTHERS => '0');
        end if;
    END PROCESS;
    
    -- ReadPort2
    PROCESS (reg_file, RA2)
        variable addr : natural;
    BEGIN
        addr := to_integer(unsigned(RA2));
        if (addr < 23) then
            RD2 <= reg_file(addr);
        else
            RD2 <= (OTHERS => '0');
        end if;
    END PROCESS;

   ---------------------------------- 

END behav;
