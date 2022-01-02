`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/22 11:23:04
// Design Name: 
// Module Name: decoder_2x4
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module decoder_2x4(
    input i_en,
    input [1:0] i_select,
    output [3:0] o_dig_select
    );
    
    reg [3:0] r_dig_select; // use register for safe function
    
    // difine output use register
    assign o_dig_select = r_dig_select;
    
    // define decoding 
    always @ (i_select, i_en) begin
        if (i_en == 0) r_dig_select <= 4'b0000;
        else
            case (i_select)
                0 : r_dig_select <= 4'b0001;
                1 : r_dig_select <= 4'b0010;
                2 : r_dig_select <= 4'b0100;
                3 : r_dig_select <= 4'b1000;
            endcase
    end
endmodule
