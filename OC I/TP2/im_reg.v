module im (
    input wire clk,
    input wire [31:0] addr,
    output wire [31:0] data
);
  parameter NMEM = 128;  // Number of memory entries,
  // not the same as the memory size
  parameter IM_DATA = "im_data.txt";  // file to read data from
  reg [31:0] mem[0:127];  // 32-bit memory with 128 entries
  initial begin
    $readmemh(IM_DATA, mem, 0, NMEM - 1);
  end
  assign data = mem[addr[8:2]][31:0];
endmodule

module regm (
    input wire clk,
    input wire [4:0] read1,
    read2,
    output wire [31:0] data1,
    data2,
    input wire regwrite,
    input wire [4:0] wrreg,
    input wire [31:0] wrdata
);

  parameter NMEM = 20;  // Number of memory entries,
  // not the same as the memory size
  parameter RM_DATA = "rm_data.txt";  // file to read data from

  reg [31:0] mem[0:31];  // 32-bit memory with 32 entries

  initial begin
    $readmemh(RM_DATA, mem, 0, NMEM - 1);
  end
  reg [31:0] _data1, _data2;
  always @(*) begin
    if (read1 == 5'd0) _data1 = 32'd0;
    else if ((read1 == wrreg) && regwrite) _data1 = wrdata;
    else _data1 = mem[read1][31:0];
  end

  always @(*) begin
    if (read2 == 5'd0) _data2 = 32'd0;
    else if ((read2 == wrreg) && regwrite) _data2 = wrdata;
    else _data2 = mem[read2][31:0];
  end

  assign data1 = _data1;
  assign data2 = _data2;

  always @(posedge clk) begin
    if (regwrite && wrreg != 5'd0) begin
      // write a non $zero register
      mem[wrreg] <= wrdata;
    end
  end
endmodule
