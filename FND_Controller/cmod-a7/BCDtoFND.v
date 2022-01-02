`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/22 11:35:15
// Design Name: 
// Module Name: BCDtoFND
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


module BCDtoFND(
    input i_en,
    input [3:0] i_fnd_data,
    output [7:0] o_fnd_font_out
    );
    
    reg [7:0] r_fnd_font;
    
    assign o_fnd_font_out = r_fnd_font;
    
    always @(i_fnd_data, i_en) begin
        if (i_en == 0) r_fnd_font <= 8'hff;
        else 
            case (i_fnd_data)
                0 : r_fnd_font <= 8'hc0;
                1 : r_fnd_font <= 8'hf9;
                2 : r_fnd_font <= 8'ha4;
                3 : r_fnd_font <= 8'hb0;
                4 : r_fnd_font <= 8'h99;
                5 : r_fnd_font <= 8'h92;
                6 : r_fnd_font <= 8'h82;
                7 : r_fnd_font <= 8'hf8;
                8 : r_fnd_font <= 8'h80;
                9 : r_fnd_font <= 8'h90;
                10 : r_fnd_font <= 8'h7f; // dp (dot)
                default : r_fnd_font <= 8'hff;
            endcase
    end
    
endmodule
