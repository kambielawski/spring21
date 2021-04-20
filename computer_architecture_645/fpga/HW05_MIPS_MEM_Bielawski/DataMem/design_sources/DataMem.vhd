LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;
USE work.my_package.ALL;

ENTITY DataMem IS
   PORT( 
      A        : IN  std_logic_vector (n_bits_address - 1 DOWNTO 0);
      MemWrite : IN  std_logic;
      WD       : IN  std_logic_vector (data_mem_width - 1 DOWNTO 0);
      clk      : IN  std_logic;
      rst      : IN  std_logic;
      RD       : OUT std_logic_vector (data_mem_width - 1 DOWNTO 0)
   );
END DataMem;

ARCHITECTURE behav OF DataMem IS

   -- Internal signal declarations
   SIGNAL data_mem  : mem_type(0 to data_mem_depth - 1);

BEGIN

   -- **************************** --
   -- DO NOT MODIFY or CHANGE the ---
   -- code template provided above --
   -- **************************** --
   
   ----- insert your code here ------
   
   -- data_mem <= (others => (others => '0'));
   
    data_write: PROCESS (clk, rst, MemWrite, WD)
        variable mem_addr : natural;
    BEGIN
        mem_addr := to_integer(unsigned(A));
        if (rst = '1') then
            -- load program into data_mem
            for i in data_mem'RANGE loop
                if (i < my_program_size) then
                    data_mem(i) <= my_program(i);
                else
                    data_mem(i) <= (others => '0');
                end if;
            end loop;
        -- only write to memory if MemWrite = 1 and clk is on a rising edge
        elsif (clk'EVENT and clk = '1' and MemWrite = '1') then
            if ((mem_addr >= 0) and (mem_addr < data_mem_depth)) then
                data_mem(mem_addr) <= WD;
            end if;
        end if;
    END PROCESS data_write;
    
    -- read port
    data_read: PROCESS (A, data_mem)
    BEGIN
        -- ensure address is within range of memory addresses
        if ((to_integer(unsigned(A)) >= 0) and (to_integer(unsigned(A)) < data_mem_depth)) then
            RD <= data_mem(to_integer(unsigned(A)));
        else
            RD <= (others => '0');
        end if;
    END PROCESS data_read;

   ----------------------------------    

END behav;
