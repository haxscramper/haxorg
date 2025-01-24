// src/renderer/visualization.ts
import * as d3 from 'd3';

export class CircleVisualization {
    private svg: d3.Selection<SVGSVGElement, unknown, HTMLElement, any>;
    private data: number[];

    constructor(containerId: string, width: number = 400, height: number = 200) {
        this.data = Array.from({length: 5}, () => Math.random() * 100);
        
        this.svg = d3.select(`#${containerId}`)
            .append('svg')
            .attr('width', width)
            .attr('height', height);
    }

    render(): void {
        this.svg.selectAll('circle')
            .data(this.data)
            .join('circle')
            .attr('cx', (d: number, i: number) => i * 80 + 40)
            .attr('cy', 100)
            .attr('r', (d: number) => d / 4)
            .style('fill', 'steelblue')
            .on('mouseover', function(this: SVGCircleElement) {
                d3.select(this)
                    .transition()
                    .duration(200)
                    .style('fill', 'red');
            })
            .on('mouseout', function(this: SVGCircleElement) {
                d3.select(this)
                    .transition()
                    .duration(200)
                    .style('fill', 'steelblue');
            });
    }
}
