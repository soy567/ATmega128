`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/22 11:47:29
// Design Name: 
// Module Name: fnd_controller
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


module fnd_controller(
    input i_en,
    input [1:0] i_select,
    input [3:0] i_fnd_data,
    output [3:0] o_dig_select,
    output [7:0] o_fnd_font_out
    );
    
    // module instantiation
    decoder_2x4(
        .i_en (i_en),
        .i_select (i_select),
        .o_dig_select (o_dig_select)
    );
    
    // module instantiation
    BCDtoFND(
        .i_en (i_en),
        .i_fnd_data (i_fnd_data),
        .o_fnd_font_out (o_fnd_font_out)
    );
    
endmodule
