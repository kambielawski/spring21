LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;
USE work.my_package.ALL;

ENTITY CU IS
   PORT( 
      Instr      : IN     std_logic_vector (n_bits_instr - 1 DOWNTO 0);
      ALUControl : OUT    std_logic_vector (n_bits_of(n_functions_alu) - 1 DOWNTO 0);
      ALUSrc     : OUT    std_logic;
      BEQ        : OUT    std_logic;
      J          : OUT    std_logic;
      MemToReg   : OUT    std_logic;
      MemWrite   : OUT    std_logic;
      RegDst     : OUT    std_logic;
      RegWrite   : OUT    std_logic
   );
END CU;

ARCHITECTURE behav OF CU IS

	SIGNAL opcode : NATURAL RANGE 0 TO (2**(opcode_end - opcode_start + 1) - 1);
	SIGNAL funct  : NATURAL RANGE 0 TO (2**(funct_end - funct_start + 1) - 1);
	SIGNAL ALUControl_int : NATURAL RANGE 0 TO (n_functions_alu - 1);

BEGIN

   -- **************************** --
   -- DO NOT MODIFY or CHANGE the ---
   -- code template provided above --
   -- **************************** --
   
    ----- insert your code here ------
    opcode <= to_integer(unsigned(Instr(opcode_end downto opcode_start)));
    funct <= to_integer(unsigned(Instr(funct_end downto funct_start)));
    
    ALUControl <= std_logic_vector(to_unsigned(ALUControl_int, n_bits_of(n_functions_alu)));
   
    process (Instr, opcode, funct)
    begin
        -- all outputs should be zero by default
        ALUSrc <= '0';      -- 1 if 2nd ALU operand should be immediate value (from instr), 0 if from registers
        BEQ <= '0';         -- 1 if instr is beq
        J <= '0';           -- 1 if instr is j    
        MemToReg <= '0';    -- load word from memory
        MemWrite <= '0';    -- 1 if writing data to memory (store word)
        RegDst <= '0';      -- 1 if R-type instruction 
        RegWrite <= '0';    -- 1 if writing data to registers (R-types)
        case opcode is
            when 0 =>
                RegDst <= '1';
                RegWrite <= '1';
                case funct is
                    when 36 =>  -- AND - 100100
                        ALUControl_int <= 0;
                    when 37 => -- OR - 100101
                        ALUControl_int <= 1;
                    when 32 => -- ADD - 100000
                        ALUControl_int <= 2;
                    when 34 => -- SUB - 100010
                        ALUControl_int <= 6;
                    when 42 => -- SLT - 101010
                        ALUControl_int <= 7;
                    when 39 => -- NOR - 100111
                        ALUControl_int <= 12;
                    when others =>
                        ALUControl_int <= 0;
                        RegDst <= '0';
                        RegWrite <= '0';
                end case;
            when 35 => -- load word - 100011
                ALUSrc <= '1';
                MemToReg <= '1';
                RegWrite <= '1';
                ALUControl_int <= 2; -- add 
            when 43 => -- store word - 101011
                ALUSrc <= '1';
                MemWrite <= '1';
                ALUControl_int <= 2; -- add
            when 4 => -- BEQ - 000100
                BEQ <= '1';
                ALUControl_int <= 6; -- sub
            when 2 => -- jump (J) - 000010
                J <= '1';
                ALUControl_int <= 0; -- and 
            when 8 => -- addi - 001000
                ALUSrc <= '1';
                RegWrite <= '1';
                ALUControl_int <= 2; -- add
            when others =>
                ALUControl_int <= 0;
        end case;
    end process;


    ----------------------------------  

END behav;
