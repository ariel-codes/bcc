/*
 * cpu. - five stage MIPS CPU.
 *
 */


`include "regr.v"
`include "im_reg.v"
`include "alu.v"
`include "control.v"
`include "datam.v"



module cpu (
    input wire clk
);

  parameter NMEM = 7;  // number in instruction memory
  parameter IM_DATA = "im_data.txt";

  wire regwrite_s5;
  wire [4:0] wrreg_s5;
  wire [31:0] wrdata_s5;
  reg stall_s1_s2;

  // {{{ flush control
  reg flush_s1, flush_s2, flush_s3;
  always @(*) begin
    flush_s1 <= 1'b0;
    flush_s2 <= 1'b0;
    flush_s3 <= 1'b0;
    if (pcsrc | jump_s4) begin
      flush_s1 <= 1'b1;
      flush_s2 <= 1'b1;
      flush_s3 <= 1'b1;
    end
  end
  // }}}

  // {{{ stage 1, IF (fetch)

  reg [5:0] clock_counter;
  initial begin
    clock_counter <= 6'd1;
  end
  always @(posedge clk) begin
    clock_counter <= clock_counter + 1;
  end

  reg [31:0] pc;
  initial begin
    pc <= 32'd0;
  end

  wire [31:0] pc4;  // PC + 4
  assign pc4 = pc + 4;

  always @(posedge clk) begin
    if (stall_s1_s2) pc <= pc;
    else if (pcsrc == 1'b1) pc <= baddr_s4;
    else if (jump_s4 == 1'b1) pc <= jaddr_s4;
    else pc <= pc4;
  end

  // pass PC + 4 to stage 2
  wire [31:0] pc4_s2;
  regr #(
      .N(32)
  ) regr_pc4_s2 (
      .clk(clk),
      .hold(stall_s1_s2),
      .clear(flush_s1),
      .in(pc),
      .out(pc4_s2)
  );

  // instruction memory
  wire [31:0] inst;
  wire [31:0] inst_s2;
  im #(
      .NMEM(NMEM),
      .IM_DATA(IM_DATA)
  ) im1 (
      .clk (clk),
      .addr(pc),
      .data(inst)
  );
  regr #(
      .N(32)
  ) regr_im_s2 (
      .clk(clk),
      .hold(stall_s1_s2),
      .clear(flush_s1),
      .in(inst),
      .out(inst_s2)
  );

  // }}}

  // {{{ stage 2, ID (decode)

  `include "decodefields.v"


  // transfer register data to stage 3
  wire [31:0] data1_s3, data2_s3;
  regr #(
      .N(64)
  ) reg_s2_mem (
      .clk(clk),
      .clear(flush_s2),
      .hold(stall_s1_s2),
      .in({data1, data2}),
      .out({data1_s3, data2_s3})
  );


  // transfer PC + 4 to stage 3
  wire [31:0] pc4_s3;
  regr #(
      .N(32)
  ) reg_pc4_s2 (
      .clk(clk),
      .clear(1'b0),
      .hold(stall_s1_s2),
      .in(pc4_s2),
      .out(pc4_s3)
  );




  // transfer the control signals to stage 3
  wire regdst_s3;
  wire memread_s3;
  wire memwrite_s3;
  wire memtoreg_s3;
  wire [1:0] aluop_s3;
  wire regwrite_s3;
  wire alusrc_s3;
  // A bubble is inserted by setting all the control signals
  // to zero (stall_s1_s2).
  regr #(
      .N(8)
  ) reg_s2_control (
      .clk(clk),
      .clear(stall_s1_s2),
      .hold(1'b0),
      .in({regdst, memread, memwrite, memtoreg, aluop, regwrite, alusrc}),
      .out({regdst_s3, memread_s3, memwrite_s3, memtoreg_s3, aluop_s3, regwrite_s3, alusrc_s3})
  );

  wire branch_eq_s3, branch_ne_s3, branch_lt_s3;
  regr #(
      .N(3)
  ) branch_s2_s3 (
      .clk(clk),
      .clear(flush_s2),
      .hold(1'b0),
      .in({branch_eq_s2, branch_ne_s2, branch_lt_s2}),
      .out({branch_eq_s3, branch_ne_s3, branch_lt_s3})
  );

  wire [31:0] baddr_s3;
  regr #(
      .N(32)
  ) baddr_s2_s3 (
      .clk(clk),
      .clear(flush_s2),
      .hold(1'b0),
      .in(baddr_s2),
      .out(baddr_s3)
  );

  wire jump_s3;
  regr #(
      .N(1)
  ) reg_jump_s3 (
      .clk(clk),
      .clear(flush_s2),
      .hold(1'b0),
      .in(jump_s2),
      .out(jump_s3)
  );

  wire [31:0] jaddr_s3;
  regr #(
      .N(32)
  ) reg_jaddr_s3 (
      .clk(clk),
      .clear(flush_s2),
      .hold(1'b0),
      .in(jaddr_s2),
      .out(jaddr_s3)
  );
  // }}}

  // {{{ stage 3, EX (execute)

  reg [31:0] fw_data1_s3;
  `include "execute.v"

  // pass through some control signals to stage 4
  wire regwrite_s4;
  wire memtoreg_s4;
  wire memread_s4;
  wire memwrite_s4;
  regr #(
      .N(4)
  ) reg_s3 (
      .clk(clk),
      .clear(flush_s2),
      .hold(1'b0),
      .in({regwrite_s3, memtoreg_s3, memread_s3, memwrite_s3}),
      .out({regwrite_s4, memtoreg_s4, memread_s4, memwrite_s4})
  );


  always @(*)
    case (forward_a)
      2'd1: fw_data1_s3 = alurslt_s4;
      2'd2: fw_data1_s3 = wrdata_s5;
      default: fw_data1_s3 = data1_s3;
    endcase

  wire zero_s4;
  regr #(
      .N(1)
  ) reg_zero_s3_s4 (
      .clk(clk),
      .clear(1'b0),
      .hold(1'b0),
      .in(zero_s3),
      .out(zero_s4)
  );

  // pass ALU result and zero to stage 4
  wire [31:0] alurslt_s4;
  regr #(
      .N(32)
  ) reg_alurslt (
      .clk(clk),
      .clear(flush_s3),
      .hold(1'b0),
      .in({alurslt}),
      .out({alurslt_s4})
  );

  // pass data2 to stage 4
  wire [31:0] data2_s4;
  reg  [31:0] fw_data2_s3;
  always @(*)
    case (forward_b)
      2'd1: fw_data2_s3 = alurslt_s4;
      2'd2: fw_data2_s3 = wrdata_s5;
      default: fw_data2_s3 = data2_s3;
    endcase
  regr #(
      .N(32)
  ) reg_data2_s3 (
      .clk(clk),
      .clear(flush_s3),
      .hold(1'b0),
      .in(fw_data2_s3),
      .out(data2_s4)
  );


  // pass to stage 4
  regr #(
      .N(5)
  ) reg_wrreg (
      .clk(clk),
      .clear(flush_s3),
      .hold(1'b0),
      .in(wrreg),
      .out(wrreg_s4)
  );

  wire branch_eq_s4, branch_ne_s4, branch_lt_s4;
  regr #(
      .N(3)
  ) branch_s3_s4 (
      .clk(clk),
      .clear(flush_s3),
      .hold(1'b0),
      .in({branch_eq_s3, branch_ne_s3, branch_lt_s3}),
      .out({branch_eq_s4, branch_ne_s4, branch_lt_s4})
  );

  wire [31:0] baddr_s4;
  regr #(
      .N(32)
  ) baddr_s3_s4 (
      .clk(clk),
      .clear(flush_s3),
      .hold(1'b0),
      .in(baddr_s3),
      .out(baddr_s4)
  );

  wire jump_s4;
  regr #(
      .N(1)
  ) reg_jump_s4 (
      .clk(clk),
      .clear(flush_s3),
      .hold(1'b0),
      .in(jump_s3),
      .out(jump_s4)
  );

  wire [31:0] jaddr_s4;
  regr #(
      .N(32)
  ) reg_jaddr_s4 (
      .clk(clk),
      .clear(flush_s3),
      .hold(1'b0),
      .in(jaddr_s3),
      .out(jaddr_s4)
  );
  // }}}

  // {{{ stage 4, MEM (memory)

  // pass regwrite and memtoreg to stage 5
  wire memtoreg_s5;
  regr #(
      .N(2)
  ) reg_regwrite_s4 (
      .clk(clk),
      .clear(1'b0),
      .hold(1'b0),
      .in({regwrite_s4, memtoreg_s4}),
      .out({regwrite_s5, memtoreg_s5})
  );

  // data memory
  wire [31:0] rdata;
  dm dm1 (
      .clk(clk),
      .addr(alurslt_s4[8:2]),
      .rd(memread_s4),
      .wr(memwrite_s4),
      .wdata(data2_s4),
      .rdata(rdata)
  );
  // pass read data to stage 5
  wire [31:0] rdata_s5;
  regr #(
      .N(32)
  ) reg_rdata_s4 (
      .clk(clk),
      .clear(1'b0),
      .hold(1'b0),
      .in(rdata),
      .out(rdata_s5)
  );

  // pass alurslt to stage 5
  wire [31:0] alurslt_s5;
  regr #(
      .N(32)
  ) reg_alurslt_s4 (
      .clk(clk),
      .clear(1'b0),
      .hold(1'b0),
      .in(alurslt_s4),
      .out(alurslt_s5)
  );

  // pass wrreg to stage 5
  regr #(
      .N(5)
  ) reg_wrreg_s4 (
      .clk(clk),
      .clear(1'b0),
      .hold(1'b0),
      .in(wrreg_s4),
      .out(wrreg_s5)
  );

  // branch
  reg pcsrc;
  always @(*) begin
    case (1'b1)
      branch_eq_s4: pcsrc <= zero_s4;
      branch_ne_s4: pcsrc <= ~(zero_s4);
      branch_lt_s4: pcsrc <= alurslt_s4[31];

      default: pcsrc <= 1'b0;
    endcase
  end
  // }}}

  // {{{ stage 5, WB (write back)

  assign wrdata_s5 = (memtoreg_s5 == 1'b1) ? rdata_s5 : alurslt_s5;

  // }}}

  // {{{ forwarding

  // stage 3 (MEM) -> stage 2 (EX)
  // stage 4 (WB) -> stage 2 (EX)

  reg [1:0] forward_a;
  reg [1:0] forward_b;
  always @(*) begin
    // If the previous instruction (stage 4) would write,
    // and it is a value we want to read (stage 3), forward it.

    // data1 input to ALU
    if ((regwrite_s4 == 1'b1) && (wrreg_s4 == rs1_s3)) begin
      forward_a <= 2'd1;  // stage 4
    end else if ((regwrite_s5 == 1'b1) && (wrreg_s5 == rs1_s3)) begin
      forward_a <= 2'd2;  // stage 5
    end else forward_a <= 2'd0;  // no forwarding

    // data2 input to ALU
    if ((regwrite_s4 == 1'b1) & (wrreg_s4 == rs2_s3)) begin
      forward_b <= 2'd1;  // stage 5
    end else if ((regwrite_s5 == 1'b1) && (wrreg_s5 == rs2_s3)) begin
      forward_b <= 2'd2;  // stage 5
    end else forward_b <= 2'd0;  // no forwarding
  end
  // }}}

  // {{{ load use data hazard detection, signal stall

  /* If an operation in stage 4 (MEM) loads from memory (e.g. lw)
	 * and the operation in stage 3 (EX) depends on this value,
	 * a stall must be performed.  The memory read cannot
	 * be forwarded because memory access is too slow.  It can
	 * be forwarded from stage 5 (WB) after a stall.
	 *
	 *   lw $1, 16($10)  ; I-type, rt_s3 = $1, memread_s3 = 1
	 *   sw $1, 32($12)  ; I-type, rt_s2 = $1, memread_s2 = 0
	 *
	 *   lw $1, 16($3)  ; I-type, rt_s3 = $1, memread_s3 = 1
	 *   sw $2, 32($1)  ; I-type, rt_s2 = $2, rs_s2 = $1, memread_s2 = 0
	 *
	 *   lw  $1, 16($3)  ; I-type, rt_s3 = $1, memread_s3 = 1
	 *   add $2, $1, $1  ; R-type, rs_s2 = $1, rt_s2 = $1, memread_s2 = 0
	 */
  always @(*) begin
    if (memread_s3 == 1'b1 && ((rs2 == rd_s3) || (rs1 == rd_s3))) begin
      stall_s1_s2 <= 1'b1;  // perform a stall
    end else stall_s1_s2 <= 1'b0;  // no stall
  end
  // }}}

endmodule


module top;
  reg clk;

  initial begin
    clk = 0;
    forever #1 clk = ~clk;
  end
  //altere aqui, de acordo com o numero de instruções no programa
  parameter nInstrucoes = 50;
  cpu #(nInstrucoes) CPU (clk);
  initial begin
    $dumpfile("test.vcd");
    $dumpvars(0, top);
    #256 $writememh("mem.data", top.CPU.dm1.mem, 0, 15);
    $writememh("reg.data", top.CPU.regm1.mem, 0, 15);
    $dumpoff;
    $finish;
  end

endmodule
