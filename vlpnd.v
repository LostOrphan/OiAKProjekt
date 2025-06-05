module division(
    input wire clk,
    input wire rst,
    input wire start,
    input wire [31:0] A,
    input wire [31:0] D,
    output reg [63:0] R,
    output reg busy,
    output reg done
);
    reg divide;
    reg [6:0] leading_D, leading_R;
    reg [63:0] R_reg;
    reg [31:0] D_reg;
    integer shift_amount;
    integer count;
    reg running;
    reg [32:0] difference;
    function  [6:0] count_leading_zeros_32(input logic [31:0] val);
        integer i;
        begin
            count_leading_zeros_32 = 32;
            for (i = 31; i >= 0; i = i - 1) begin
                if (val[i]) begin
                    count_leading_zeros_32 = 31 - i;
                    i=-1;
                end
            end
        end
    endfunction

    function  [6:0] count_leading_zeros_64(input logic [63:0] val);
        integer i;
        begin
            count_leading_zeros_64 = 64;
            for (i = 63; i >= 0; i = i - 1) begin
                if (val[i]) begin
                    count_leading_zeros_64 = 63 - i;
                    i=-1;
                end
            end
        end
    endfunction
    always @(posedge clk or posedge rst) begin
        if(rst) begin
            busy<=0;
            done<=0;
            running<=0;
        end
        else begin
            if(start && !running) begin
                R_reg<={32'b0, A};
                D_reg<=D;
                count<=0;
                busy<=1;
                done<=0;
                running<=0;
            end
       
        else if(busy) begin
            leading_D = count_leading_zeros_32(D_reg);
            leading_R = count_leading_zeros_64(R_reg);

            //Dynamic Shift
            shift_amount = leading_R - leading_D -1;
            if(shift_amount>0)begin
                if(shift_amount>(31-count))
                    shift_amount= 31-count;
                R_reg<= R_reg << shift_amount;
                count<= count+shift_amount;    
            end
            //Classic Division
            difference=((R_reg[62:31]) - D_reg); 
            R_reg=R_reg << 1;
            if(!difference[32]) begin   // if >=0
                R_reg[63:32]=difference[31:0];
                R_reg[0]=1'b1;
            end
            count=count+1;
            if(count==32)begin
                busy<=0;
                done<=1;
                running<=0;
                R<=R_reg;
                done=0;
            end
        end
    end
end
endmodule