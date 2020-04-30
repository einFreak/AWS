
//Call Diag
$(document).ready(
	function() {
		console.log( "ready for Diagramms!" );
		drawDiag1();
		console.log( "Diag1 drawn" );
		drawDiag2();
		console.log( "Diag2 drawn" );
	}
);

function drawDiag1(){
    var line1 = [6.5, 9.2, 14, 19.65, 26.4, 35, 51];
 
    var plot1 = $.jqplot('P1_Diag', [line1], {
        legend: {show:false},
        axes:
		{
			xaxis:
			{
				tickOptions:
					{ 
					angle: -30
					},
				labelOptions:
					{
					fontFamily:'Helvetica',
					fontSize: '14pt'
					},
				tickRenderer:$.jqplot.CanvasAxisTickRenderer,
				labelRenderer: $.jqplot.CanvasAxisLabelRenderer,
				label:'Core Motor Amperage' 
			}, 
			yaxis:
			{
				tickOptions:
					{
					labelPosition: 'middle', 
					angle:-30
					},
				labelOptions:
					{
					fontFamily:'Helvetica',
					fontSize: '14pt'
					},
				renderer:$.jqplot.LogAxisRenderer,	
				tickRenderer:$.jqplot.CanvasAxisTickRenderer,
				labelRenderer: $.jqplot.CanvasAxisLabelRenderer,
				label:'Core Motor Voltage'
			}
		}
    });
};


function drawDiag2(){   
    var line2 = [['1/1/2008', 42], ['2/14/2008', 56], ['3/7/2008', 39], ['4/22/2008', 81]];
    var plot2 = $.jqplot('P2_Diag', [line2], {
      axes: {
        xaxis: {
          renderer: $.jqplot.DateAxisRenderer,
          label: 'Incliment Occurrance',
          labelRenderer: $.jqplot.CanvasAxisLabelRenderer,
          tickRenderer: $.jqplot.CanvasAxisTickRenderer,
          tickOptions: {
              // labelPosition: 'middle',
              angle: 15
          }
		
        },
        yaxis: {
          label: 'Incliment Factor',
          labelRenderer: $.jqplot.CanvasAxisLabelRenderer
        }
      }
    });
 
};