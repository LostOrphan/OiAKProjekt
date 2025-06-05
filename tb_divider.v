`timescale 1ns / 1ps

module division_tb;

  // Testbench signals
  reg clk;
  reg rst;
  reg start;
  reg [31:0] A;
  reg [31:0] D;
  wire [63:0] R;
  wire busy;
  wire done;

  // Instantiate the Unit Under Test (UUT)
  division uut (
    .clk(clk),
    .rst(rst),
    .start(start),
    .A(A),
    .D(D),
    .R(R),
    .busy(busy),
    .done(done)
  );

  // Clock generation: 10ns period
  initial clk = 0;
  always #5 clk = ~clk;

  // Task to wait for 'done' signal
  task wait_for_done;
    begin
      wait (done);
      #10; // Let outputs settle
      $display("Result: Quotient = %0d, Remainder = %0d", R[31:0], R[63:32]);
    end
  endtask

  // Test stimulus
  initial begin
    // Initialize inputs
    rst = 1;
    start = 0;
    A = 0;
    D = 0;

    // Reset sequence
    #20;
    rst = 0;

    // Test Case 1: 100 / 3
    A = 100;
    D = 3;
    start = 1;
    #10 start = 0;
    wait_for_done();

    // Test Case 2: 200 / 10
    A = 200;
    D = 10;
    start = 1;
    #10 start = 0;
    wait_for_done();

    // Test Case 3: 12345678 / 1234
    A = 32'd12345678;
    D = 32'd1234;
    start = 1;
    #10 start = 0;
    wait_for_done();

    // Test Case 4: 2^31 / 2
    A = 32'h80000000;
    D = 2;
    start = 1;
    #10 start = 0;
    wait_for_done();

    // End of test
    $display("All tests completed.");
    $finish;
  end

endmodule