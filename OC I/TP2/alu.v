module alu (
    input		[3:0]	ctl,
    input		[31:0]	a,
    b,
    output reg	[31:0]	out,
    output				zero
);

  wire [31:0] sub_ab;
  wire [31:0] add_ab;
  wire oflow_add;
  wire oflow_sub;
  wire oflow;
  wire slt;

  assign zero = (0 == out);

  assign sub_ab = a - b;
  assign add_ab = a + b;
  assign oflow_add = (a[31] == b[31] && add_ab[31] != a[31]) ? 1 : 0;
  assign oflow_sub = (a[31] == b[31] && sub_ab[31] != a[31]) ? 1 : 0;
  assign oflow = (ctl == 4'b0010) ? oflow_add : oflow_sub;
  // set if less than, 2s compliment 32-bit numbers
  assign slt = oflow_sub ? ~(a[31]) : a[31];
  always @(*) begin
    case (ctl)
      4'd0: out <= a & b;  // and
      4'd1: out <= a | b;  // or
      4'd2: out <= add_ab;  // add
      4'd6: out <= sub_ab;  // sub
      4'd7: out <= {{31{1'b0}}, slt};  // slt
      4'd12: out <= ~(a | b);  // nor
      4'd13: out <= a ^ b;  // xor
      4'd16: out <= a << b[4:0];  // shift left
      default: out <= 0;
    endcase
  end

endmodule


module alu_control (
    input  wire [3:0] funct,
    input  wire [1:0] aluop,
    output reg  [3:0] aluctl
);

  reg [3:0] _funct;

  always @(*) begin
    case (funct[3:0])
      4'b0000: _funct = 4'd02;  // ADD
      4'b0001: _funct = 4'd16;  // SLL
      4'b0010: _funct = 4'd07;  // SLT
      4'b0100: _funct = 4'd13;  // XOR
      4'b0110: _funct = 4'd01;  // OR
      4'b0111: _funct = 4'd12;  // NOR
      4'b0111: _funct = 4'd00;  // AND
      4'b1000: _funct = 4'd06;  // SUB
      default: _funct = 4'd00;
    endcase
  end

  always @(*) begin
    case (aluop)
      2'b00:   aluctl = 4'd2;  // add
      2'b01:   aluctl = 4'd6;  // sub
      2'b10:   aluctl = _funct;  // use funct3 field
      2'b11:   aluctl = 4'd2;  // add
      default: aluctl = 0;
    endcase
  end

endmodule
