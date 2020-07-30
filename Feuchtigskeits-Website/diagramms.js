//Call Diag
$(document).ready(
	function() {
		console.log( "ready for Diagramms!" );
		drawDiag1(hum_data);
		console.log( "Diag1 drawn" );
		drawDiag2(temp_data);
		console.log( "Diag2 drawn" );
	}
);

var plot1;
function drawDiag1(line1){
 
    if (plot1) plot1.destroy();
	plot1 = $.jqplot('P1_Diag', [line1], {
        title: 'Moisture',
		grid: {
            backgroundColor: "#444444",
            gridLineColor: '#999999',
            gridLineWidth: 2
        },
		stackSeries: true,
		showMarker: false,
		seriesDefaults: {
			fill: true,
			fillToZero: true,
			rendererOptions: {
                smooth: true
			}
		},
		 series: [
            {color: 'rgba(25, 200, 255, 0.4)'}
		],
		legend: {show:false},
        axesDefaults: {
            tickRenderer:$.jqplot.CanvasAxisTickRenderer,
			labelRenderer: $.jqplot.CanvasAxisLabelRenderer,
            tickOptions: {
                angle: -30,
                fontSize: '10pt'
            },
			labelOptions:
			{
				fontFamily:'Helvetica',
				fontSize: '14pt'
			},
			tickOptions:
			{ 
				angle: -30
			},
            showMinorTicks:true
        },
		axes:
		{
			xaxis:
			{
				tickOptions:
				{
					formatString: "%d.%m.%y - %H:%M:%S"
				},
				// tickInterval: '1 minute',
				renderer: $.jqplot.DateAxisRenderer,
				label:'Timestamp' 
			}, 
			yaxis:
			{
				min: 0,
				max: 100,
				label:'Feuchtigkeit'
			}
		},
		highlighter: {
			show: true,
			sizeAdjust: 7.5,
			tooltipAxes: "y",
			tooltipFormatString: '%d %',
			useAxesFormatters: false
		},
		cursor: {
			show: false
		}
    });
};

var plot2;
function drawDiag2(line2){
 
    if (plot2) plot2.destroy();
	plot2 = $.jqplot('P2_Diag', [line2], {
        title:'Temperatur',
		grid: {
            backgroundColor: "#444444",
            gridLineColor: '#999999',
            gridLineWidth: 2
        },
		stackSeries: true,
		showMarker: false,
		seriesDefaults: {
			fill: true,
			fillToZero: true,
			rendererOptions: {
                smooth: true
			}
		},
		 series: [
            {color: 'rgba(190, 0, 0, 0.4)'}
		],
		
		legend: {show:false},
        axesDefaults: {
            tickRenderer:$.jqplot.CanvasAxisTickRenderer,
			labelRenderer: $.jqplot.CanvasAxisLabelRenderer,
            tickOptions: {
                angle: -30,
                fontSize: '10pt'
            },
			labelOptions:
			{
				fontFamily:'Helvetica',
				fontSize: '14pt'
			},
			tickOptions:
			{ 
				angle: -30
			},
            showMinorTicks:true
        },
        axes:
		{
			xaxis:
			{
				tickOptions:
					{
					formatString: "%d.%m.%y - %H:%M:%S"
					},
				//tickInterval: '1 minute',
				renderer: $.jqplot.DateAxisRenderer,
				label:'Timestamp' 
			}, 
			yaxis:
			{
				tickOptions:
					{
					labelPosition: 'middle'
					},
				max: 30,
				label:'Temperatur'
			}
		},
		highlighter: {
			show: true,
			sizeAdjust: 7.5,
			tooltipAxes: "y",
			tooltipFormatString: '%d °C',
			useAxesFormatters: false
		},
		cursor: {
			show: false
		}
    });
};