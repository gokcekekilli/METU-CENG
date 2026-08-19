// StudentTemplate.v
// CENG232 Lab 1 - Student submission template
// IMPORTANT: Do not change module name or port names.

module lab1(
    input  wire A1,
    input  wire A0,
    input  wire B1,
    input  wire B0,
    output wire X,
    output wire Y,
    output wire Z
);

    // YOUR IMPLEMENTATION HERE
    // Use only combinational logic (assign or always @(*)).

    // Example (REMOVE/REPLACE with your own logic):
    // assign X = 1'b0;
    // assign Y = 1'b0;
    // assign Z = 1'b0;
   
    assign X = (A1 & (A0 | B1 | B0)) | (A0 & B1 & B0);
    assign Y = ~A0 & B0 & (~A1 | ~B1);
    assign Z = (A1 & ~A0) | (B1 & ~B0) | (~B0 | B1) & ((A1 & A0) | (~A1 & ~A0));
   
endmodule