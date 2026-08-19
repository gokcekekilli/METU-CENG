module lab2 (
    input [6:0] A,
    output Z,
    output E,
    output G,
    output L,
    output I,
    output [3:0] O
);
    wire A0 = A[0];
    wire A1 = A[1];
    wire A2 = A[2];
    wire A3 = A[3];
    wire [1:0] X = {A3, A2};
    wire [1:0] Y = {A1, A0};

    wire O0_op1 = A2 ^ A0;
    wire O1_op1 = A3 ^ A1 ^ (A2 & A0);
    wire O2_op1 = (A3 & A1) | A2 & A0 & (A3 ^ A1);
    wire Z_op1 = (O1_op1 | O0_op1) ~| O2_op1;

    wire E_op2 = ~(A3 ^ A1) & ~(A2 ^ A0);
    wire G_op2 = (A3 & ~A1) | (~(A3 ^ A1) & A2 & ~A0);
    wire L_op2 = (~A3 & A1) | (~(A3 ^ A1) & ~A2 & A0);

    wire O0_op3 = ~A0;
    wire O1_op3 = A1 ^ A0;
    wire O2_op3 = A2 ^ (A0 & A1);
    wire O3_op3 = A3 ^ (A0 & A1 & A2);
    wire Z_op3 = A0 & A1 & A2 & A3;
    wire I_op3 = A0 & A1 & A2 & A3;

    wire O0_op4 = ~(A2 ^ A0);
    wire O1_op4 = ~(A3 ^ A1);
    wire Z_op4 = (~O1_op4) & (~O0_op4);

    wire O0_op5 = ~A3 & ~A2;
    wire O1_op5 = ~A3 & A2;
    wire O2_op5 = A3 & ~A2;
    wire O3_op5 = A3 & A2;
    wire Z_op5 = ~A3 & ~A2 & ~A1 & ~A0;

    wire O0_op6 = A2 & A0;
    wire O1_op6 = (A3 & A0) ^ (A2 & A1);
    wire O2_op6 = (A3 & A1) ^ (A3 & A2 & A1 & A0);
    wire O3_op6 = A3 & A2 & A1 & A0;
    wire Z_op6 = (A3 ~| A2) | (A1 ~| A0);
    
    wire E_op7 = ~(A3 ^ A1) & ~(A2 ^ A0);
    wire G_op7 = ~E_op7 & ~L_op7;
    wire L_op7 = (A3 & ~A1) | (~(A3 ^ A1) & (~A2 & A0));

    wire O0_op8 = A1 ^ A0;
    wire O1_op8 = A2 ^ A1;
    wire O2_op8 = A3 ^ A2;
    wire O3_op8 = A3;

    wire [2:0] sel = A[6:4];
    assign O =
    (sel == 3'b000) ? {1'b0, O2_op1,O1_op1,O0_op1} :
    (sel == 3'b001) ? 4'b0000 :
    (sel == 3'b010) ? {O3_op3, O2_op3,O1_op3,O0_op3}  :
    (sel == 3'b011) ? {2'b00, O1_op4, O0_op4} :
    (sel == 3'b100) ? {O3_op5, O2_op5, O1_op5, O0_op5} :
    (sel == 3'b101) ? {O3_op6, O2_op6, O1_op6, O0_op6}:
    (sel == 3'b110) ? 4'b0000 :
                         {O3_op8, O2_op8, O1_op8, O0_op8};
    
    assign Z =
    (sel == 3'b000) ? Z_op1 :
    (sel == 3'b001) ? 1'b0 :
    (sel == 3'b010) ? Z_op3 :
    (sel == 3'b011) ? Z_op4 :
    (sel == 3'b100) ? Z_op5 :
    (sel == 3'b101) ? Z_op6 :
    (sel == 3'b110) ? 1'b0 :
                         1'b0;
    
    assign E =
    (sel == 3'b001) ? E_op2 :
    (sel == 3'b110) ? E_op7 :
                         1'b0;

    assign G =
    (sel == 3'b001) ? G_op2 :
    (sel == 3'b110) ? G_op7 :
                         1'b0;
    assign L =
    (sel == 3'b001) ? L_op2 :
    (sel == 3'b110) ? L_op7 :
                         1'b0;
    
    assign I =
    (sel == 3'b010) ? I_op3 :
                         1'b0;
endmodule