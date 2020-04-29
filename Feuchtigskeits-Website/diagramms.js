function drawDiag(){
    var line1 = [6.5, 9.2, 14, 19.65, 26.4, 35, 51];
 
    var plot1 = $.jqplot('P1_Diag', [line1], {
        legend: {show:false},
        axes:{
          xaxis:{
          tickOptions:{ 
            angle: -30
          },
          tickRenderer:$.jqplot.CanvasAxisTickRenderer,
            label:'Core Motor Amperage', 
          labelOptions:{
            fontFamily:'Helvetica',
            fontSize: '14pt'
          },
          labelRenderer: $.jqplot.CanvasAxisLabelRenderer
          }, 
          yaxis:{
            renderer:$.jqplot.LogAxisRenderer,
            tickOptions:{
                labelPosition: 'middle', 
                angle:-30
            },
            tickRenderer:$.jqplot.CanvasAxisTickRenderer,
            labelRenderer: $.jqplot.CanvasAxisLabelRenderer,
            labelOptions:{
                fontFamily:'Helvetica',
                fontSize: '14pt'
            },
            label:'Core Motor Voltage'
          }
        }
    });
 
});