`timescale 1ns / 1ps

module division_tb;

  // Sygnaly testowe
  reg clk;
  reg rst;
  reg start;
  reg [31:0] A;
  reg [31:0] D;
  wire [63:0] R;
  wire busy;
  wire done;

  // Instancja modułu dzielnika
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

  // Generowanie zegara o okresie 10 ns
  initial clk = 0;
  always #5 clk = ~clk;

  // Zadanie oczekiwania na zakończenie operacji dzielenia
  task wait_for_done;
    begin
      wait (done);
      #10; // Przerwa dla stabilizacji sygnałów
      $display("Wynik: Iloraz = %0d, Reszta = %0d", R[31:0], R[63:32]);
    end
  endtask

  // Sekwencja testowa
  initial begin
    // Inicjalizacja sygnałów
    rst = 1;
    start = 0;
    A = 0;
    D = 0;

    // Resetowanie modułu
    #20;
    rst = 0;

    // Test 1: 100/3
    A = 100;
    D = 3;
    start = 1;
    #10 start = 0;
    wait_for_done();

    // Test 2: 50/5
    A = 50;
    D = 5;
    start = 1;
    #10 start = 0;
    wait_for_done();
    // Koniec testu 
    $display("Wszystkie testu zostaly zakonczone.");
    $finish;
  end

endmodule