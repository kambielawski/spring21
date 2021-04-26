LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;
USE work.my_package.ALL;

ENTITY ALU IS
   PORT( 
      A           : IN     std_logic_vector (n_bits_alu  - 1 DOWNTO 0);
      ALUControl  : IN     std_logic_vector (n_bits_of(n_functions_alu) - 1 DOWNTO 0);
      B           : IN     std_logic_vector (n_bits_alu  - 1 DOWNTO 0);
      C           : OUT    std_logic_vector (n_bits_alu  - 1 DOWNTO 0);
      zero        : OUT    std_logic;
      overflow    : OUT    std_logic
   );
END ALU;

ARCHITECTURE behav OF ALU IS

   -- Internal signal declarations
   SIGNAL ALUControl_int : natural RANGE 0 TO (n_functions_alu - 1);
   SIGNAL C_internal : std_logic_vector(n_bits_alu  - 1 DOWNTO 0);
   SIGNAL s_A, s_B, s_C : std_logic; -- Sign bits of A, B, C

BEGIN

   -- **************************** --
   -- DO NOT MODIFY or CHANGE the ---
   -- code template provided above --
   -- **************************** --
   
   ----- insert your code here ------

    -- Convert ALUControl to integer type  
    ALUControl_int <= to_integer(unsigned(ALUControl));

    -- grab sign bit of A, B, C
    s_A <= A(n_bits_alu - 1);
    s_B <= B(n_bits_alu - 1);
    s_C <= C_internal(n_bits_alu - 1);

    -- ALU Functions
    alu_functions: PROCESS (ALUControl_int, A, B)
    BEGIN
        CASE ALUControl_int is
            -- AND = 0
            WHEN 0 =>
                C_internal <= A AND B;
                
            -- OR = 1
            WHEN 1 =>
                C_internal <= A OR B;
                
            -- ADD = 2
            WHEN 2 =>
                C_internal <= std_logic_vector(signed(A) + signed(B));
                
            -- SUB = 6
            WHEN 6 =>
                C_internal <= std_logic_vector(signed(A) - signed(B));
                
            -- LESS THAN = 7
            WHEN 7 =>
                if (signed(A) < signed(B)) then
                    -- set C_internal to 1
                    C_internal <= (0 => '1', others => '0');
                else
                    -- else 0
                    C_internal <= (others => '0');
                end if;
                
            -- NOR = 12
            WHEN 12 =>
                C_internal <= A NOR B;
                
            WHEN OTHERS =>
                C_internal <= (others => '0');
                
            END CASE;
    END PROCESS alu_functions;
    
    alu_flags: PROCESS (s_A, s_B, s_C, C_internal, ALUControl_int)
        variable overflow_check : std_logic_vector(2 downto 0);
    BEGIN
        
        -- set zero output
        if (to_integer(unsigned(C_internal)) = 0) then
            zero <= '1';
        else
            zero <= '0';
        end if;
        
        -- check for overflow
        overflow_check := s_A & s_B & s_C;
     
        -- addition overflow
        if (ALUControl_int = 2 and (overflow_check = "110" or overflow_check = "001")) then
            overflow <= '1';
        -- subtraction overflow
        elsif (ALUControl_int = 6 and (overflow_check = "011" or overflow_check = "100")) then
            overflow <= '1';
        -- otherwise, no overflow
        else
            overflow <= '0';
        end if;
        
        C <= C_internal;
        
    END PROCESS alu_flags;
    
   ----------------------------------    

END behav;
