LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
USE work.my_package.ALL;

ENTITY mod_m_up_dn_count IS
	GENERIC (m : NATURAL := 16);
	PORT (up_down	: IN	STD_LOGIC; -- direction of count, 1 --> counting up, 0 --> counting down
	      clk, rst	: IN	STD_LOGIC;
	      count	    : OUT	STD_LOGIC_VECTOR(n_bits_of(m) - 1 DOWNTO 0)
	     );
END mod_m_up_dn_count;

ARCHITECTURE behavioral OF mod_m_up_dn_count IS

   -- Internal signal declarations
   SIGNAL count_int : UNSIGNED(count'length - 1 DOWNTO 0) := (OTHERS => '0');

BEGIN

   -- **************************** --
   -- DO NOT MODIFY or CHANGE the ---
   -- code template provided above --
   -- **************************** --
   
   ----- insert your code here ------

    count <= std_logic_vector(count_int); -- figure out how to count_int mod m

	asynch_reset : PROCESS(clk, rst)
	BEGIN
		IF (rst ='1') THEN
			count_int <= (others => '0'); -- if rst is 1, then assign count_int to all 0's
		ELSIF (clk'EVENT AND clk = '1') THEN
			IF (up_down = '1') THEN
				if (count_int = m-1) then
				    count_int <= (others => '0');
				else
				    count_int <= count_int + 1;
				end if;
			ELSE
			    if (count_int = 0) then
			        count_int <= to_unsigned(m-1, n_bits_of(m));
			    else
				    count_int <= count_int - 1;
				end if;
			END IF;
		END IF;
	END PROCESS;

   ----------------------------------	

END behavioral;
