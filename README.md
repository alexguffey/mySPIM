# mySPIM

instruction_fetch		FINISHED

instruction_partition	FINISHED

instruction_decode		IN WORK		-how to assign chars in struct?
From Alex: Just a heads up, I was researching it a bit and the only cases you
should be taking are: r-type, addi, slti, sltiu, beq, jump, lw, load unsigned
immediate, sw

Dropper: I looked at the Project Guideline again.  Are addi, slti and so on
called by other names? I just put in the names of the instructions as they
apperead in the word document and I'm unclear as to how I should proceed.
Feeling insecure, like I let the team down, please console.


**Notes**
//ALUSrc should be 0 for R-type, 1 for I-type and branch
//ALUOp of 7 tells ALU to use funct field
//RegDst should be 1 for R-type, 0 for I-type and branch