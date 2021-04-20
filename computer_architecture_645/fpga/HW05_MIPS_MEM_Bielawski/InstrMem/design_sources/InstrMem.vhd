LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;
USE work.my_package.ALL;

ENTITY InstrMem IS
   PORT( 
      A     : IN  std_logic_vector (n_bits_address - 1 DOWNTO 0);
      rst   : IN  std_logic;
      Instr : OUT std_logic_vector (instr_mem_width - 1 DOWNTO 0)
   );
END InstrMem;

ARCHITECTURE behav OF InstrMem IS

   -- Internal signal declarations
   SIGNAL instr_mem  : mem_type(0 to instr_mem_depth - 1);

BEGIN

   -- **************************** --
   -- DO NOT MODIFY or CHANGE the ---
   -- code template provided above --
   -- **************************** --
   
   ----- insert your code here ------

    read_port: PROCESS (rst, A, instr_mem)
    BEGIN
        if (rst = '1') then
            instr_mem <= my_program;
            Instr <= zeros;
        else
            if ((to_integer(unsigned(A)) >= 0) and (to_integer(unsigned(A)) < instr_mem_depth)) then
                Instr <= instr_mem(to_integer(unsigned(A)));
            else
                Instr <= zeros;
            end if;
        end if;
    END PROCESS read_port;

   ----------------------------------    

END behav;
