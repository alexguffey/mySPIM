# mySPIM

instruction_fetch		FINISHED

instruction_partition	IN WORK		-how to set up masks?
From Alex: I was researching this a bit as well and I think you have to do them in hexadecimal. When you use binary you have to import certain new libraries. They should be:
rtypePart = 0x1f;
functPart = 0x0000003f;
offsetPart = 0x0000ffff;
jsecPart = 0x03ffffff;

instruction_decode		IN WORK		-how to assign chars in struct?
From Alex: Just a heads up, I was researching it a bit and the only cases you should be taking are: r-type, addi, slti, sltiu, beq, jump, lw, load unsigned immediate, sw