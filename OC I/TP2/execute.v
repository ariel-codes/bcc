// ALU

// second ALU input can come from an immediate value or data
wire [31:0] alusrc_data2;
assign alusrc_data2 = (alusrc_s3) ? seimm_s3 : fw_data2_s3;

// ALU control
wire [3:0] aluctl;
wire [5:0] funct;
assign funct = seimm_s3[5:0];
alu_control alu_ctl1 (
    .funct (func_s3),
    .aluop (aluop_s3),
    .aluctl(aluctl)
);

// ALU
wire [31:0] alurslt;
wire zero_s3;
alu alu1 (
    .ctl(aluctl),
    .a(fw_data1_s3),
    .b(alusrc_data2),
    .out(alurslt),
    .zero(zero_s3)
);

// write register
wire [4:0] wrreg;
wire [4:0] wrreg_s4;
assign wrreg = (regdst_s3) ? rd_s3 : rs2_s3;
