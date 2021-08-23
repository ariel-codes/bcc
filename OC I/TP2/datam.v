module dm (
    input wire clk,
    input wire [6:0] addr,
    input wire rd,
    wr,
    input wire [31:0] wdata,
    output wire [31:0] rdata
);
  parameter NMEM = 20;  // Number of memory entries,
  // not the same as the memory size
  parameter RM_DATA = "dm_data.txt";  // file to read data from

  reg [31:0] mem[0:127];  // 32-bit memory with 128 entries

  initial begin
    $readmemh(RM_DATA, mem, 0, NMEM - 1);
  end


  always @(posedge clk) begin
    if (wr) begin
      mem[addr] <= wdata;
    end
  end

  assign rdata = wr ? wdata : mem[addr];
  // During a write, avoid the one cycle delay by reading from 'wdata'

endmodule
