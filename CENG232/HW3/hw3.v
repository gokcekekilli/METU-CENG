module d_latch(
    input D,
    input EN,
    output Q,
    output Q_bar
);
    wire d_not;
    wire nand1_output, nand2_output;
    assign d_not = ~D;
    nand nand1(nand1_output, D, EN);
    nand nand2(nand2_output, d_not, EN);
    nand nand3(Q, nand1_output, Q_bar);
    nand nand4(Q_bar, nand2_output, Q);
endmodule

module d_ff(
    input D,
    input CLK,
    output Q,
    output Q_bar
);
    wire clk_not;
    wire master_q, master_q_bar;
    assign clk_not = ~CLK;
    d_latch my_master(D, clk_not, master_q, master_q_bar);
    d_latch my_slave(master_q, CLK, Q, Q_bar);
endmodule

module d_ff_psr(
    input D,
    input CLK,
    input PRE_bar,
    input CLR,
    output reg Q,
    output reg Q_bar
);
    always @(posedge CLK or negedge PRE_bar or posedge CLR) begin
        if (CLR) begin
            Q <= 1'b0;
            Q_bar <= 1'b1;
        end
        else if (!PRE_bar) begin
            Q <= 1'b1;
            Q_bar <= 1'b0;
        end
        else begin
            Q <= D;
            Q_bar <= ~D;
        end
    end
endmodule

module jk_ff(
    input J,
    input K,
    input CLK,
    input PRE_bar,
    input CLR,
    output Q,
    output Q_bar
);
    wire d_input;
    assign d_input = (J & ~Q) | (~K & Q);
    d_ff_psr my_dff(d_input, CLK, PRE_bar, CLR, Q, Q_bar);
endmodule

