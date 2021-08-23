module control (
    input wire [6:0] opcode,
    output reg branch_eq,
    branch_ne,
    branch_lt,
    output reg [1:0] aluop,
    output reg memread,
    memwrite,
    memtoreg,
    output reg regdst,
    regwrite,
    alusrc,
    output reg jump,
    output reg [31:0] ImmGen,
    input [31:0] inst
);
  wire [2:0] funct3 = inst[14:12];  //funct3 para diferenciar as instruções de branch
  always @(*) begin
    /* defaults */
    aluop[1:0] <= 2'b10;
    alusrc <= 1'b0;
    branch_eq <= 1'b0;
    branch_ne <= 1'b0;
    memread <= 1'b0;
    memtoreg <= 1'b0;
    memwrite <= 1'b0;
    regdst <= 1'b1;
    regwrite <= 1'b1;
    jump <= 1'b0;

    case (opcode)
      7'b0000011: begin  // lw == 3
        alusrc <= 1'b1;
        aluop[1:0] <= 2'b00;
        memtoreg <= 1'b1;
        regwrite <= 1'b1;
        memread <= 1'b1;
        ImmGen <= {{20{inst[31]}}, inst[31:20]};
      end
      7'b0010011: begin  // Integer Register-Immediate Instructions
        aluop <= 2'b10;  // ALU will use funct3 field
        alusrc <= 1'b1;  // Tell ALU to use immediate
        ImmGen <= {{20{inst[31]}}, inst[31:20]};  // sign-extended immediate
      end
      7'b1100011: begin  // Branch Instructions
        aluop <= 2'b01; // ALU
        ImmGen <= {{19{inst[31]}}, inst[31], inst[7], inst[30:25], inst[11:8], 1'b0};
        regwrite <= 1'b0;
        branch_eq <= funct3 == 3'b000;
        branch_ne <= funct3 == 3'b001;
        branch_lt <= funct3 == 3'b100;
      end
      7'b0100011: begin  /* sw */
        memwrite <= 1'b1;
        aluop[1] <= 1'b0;
        alusrc   <= 1'b1;
        regwrite <= 1'b0;
        ImmGen   <= {{20{inst[31]}}, inst[31:25], inst[11:7]};
      end
      7'b0110011: begin  /* add */
      end
      6'b000010: begin  /* j jump */
        jump <= 1'b1;
      end
    endcase
  end
endmodule
