wire [ 5:0] opcode;
wire [ 6:0] opcoderv;
wire [ 4:0] rs;
wire [ 4:0] rs1;
wire [ 4:0] rt;
wire [ 4:0] rs2;
wire [ 4:0] rd;
wire [ 6:0] func7;
wire [ 2:0] func3;
wire [15:0] imm;
wire [ 4:0] shamt;
wire [31:0] jaddr_s2;
wire [31:0] seimm;  // sign extended immediate
//
assign opcode   = inst_s2[31:26];
assign opcoderv = inst_s2[6:0];
assign rs       = inst_s2[25:21];
assign rs2      = inst_s2[24:20];
assign rt       = inst_s2[20:16];
assign rs1      = inst_s2[19:15];
assign rd       = inst_s2[11:7];
assign func7    = inst_s2[31:25];
assign func3    = inst_s2[14:12];
assign imm      = inst_s2[15:0];
assign shamt    = inst_s2[10:6];
assign jaddr_s2 = {pc[31:28], inst_s2[25:0], {2{1'b0}}};
assign seimm    = {{16{inst_s2[15]}}, inst_s2[15:0]};

// register file
wire [31:0] data1, data2;
regm regm1 (
    .clk(clk),
    .read1(rs1),
    .read2(rs2),
    .data1(data1),
    .data2(data2),
    .regwrite(regwrite_s5),
    .wrreg(wrreg_s5),
    .wrdata(wrdata_s5)
);

// control (opcode -> ...)
wire regdst;
wire branch_eq_s2;
wire branch_ne_s2;
wire branch_lt_s2;
wire memread;
wire memwrite;
wire memtoreg;
wire [1:0] aluop;
wire regwrite;
wire alusrc;
wire jump_s2;
wire [31:0] ImmGen;  // RISCV
//
//agora passa blt para o control
control ctl1 (
    .opcode(opcoderv),
    .regdst(regdst),
    .branch_eq(branch_eq_s2),
    .branch_ne(branch_ne_s2),
    .branch_lt(branch_lt_s2),
    .memread(memread),
    .memtoreg(memtoreg),
    .aluop(aluop),
    .memwrite(memwrite),
    .alusrc(alusrc),
    .regwrite(regwrite),
    .jump(jump_s2),
    .ImmGen(ImmGen),
    .inst(inst_s2)
);

// pass rs to stage 3 (for forwarding)
wire [4:0] rs_s3;
wire [4:0] rs1_s3;
regr #(
    .N(5)
) regr_s2_rs (
    .clk(clk),
    .clear(1'b0),
    .hold(stall_s1_s2),
    .in(rs1),
    .out(rs1_s3)
);

// transfer seimm, rt, and rd to stage 3
wire [31:0] seimm_s3;
wire [ 4:0] rt_s3;
wire [ 4:0] rs2_s3;
wire [ 4:0] rd_s3;
regr #(
    .N(32)
) reg_s2_seimm (
    .clk(clk),
    .clear(flush_s2),
    .hold(stall_s1_s2),
    .in(ImmGen),
    .out(seimm_s3)
);  // RISCV
regr #(
    .N(10)
) reg_s2_rt_rd (
    .clk(clk),
    .clear(flush_s2),
    .hold(stall_s1_s2),
    .in({rs2, rd}),
    .out({rs2_s3, rd_s3})
);

// shift left, seimm
wire [31:0] seimm_sl2;
assign seimm_sl2 = {seimm[29:0], 2'b0};  // shift left 2 bits
// branch address
wire [31:0] baddr_s2;
assign baddr_s2 = pc4_s2 + ImmGen;

wire [3:0] func_s3;

regr #(
    .N(4)
) func7_3_s2 (
    .clk(clk),
    .clear(1'b0),
    .hold(stall_s1_s2),
    .in({func7[5], func3}),
    .out(func_s3)
);
