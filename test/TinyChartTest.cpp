#include "TinyUtil.h"
#include "TinyChart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory>


int main(int argc, char **argv)
{
    printf("-- write image by gd ---");
    {
        STR_VEC xScales;
        xScales.reserve(10);
        xScales.push_back("11-09");
        xScales.push_back("11-10");
        xScales.push_back("11-11");
        xScales.push_back("11-12");
        xScales.push_back("11-13");
        xScales.push_back("11-14");
        xScales.push_back("11-15");
        xScales.push_back("11-16");
        xScales.push_back("11-17");
        xScales.push_back("11-18");
        xScales.push_back("11-19");
        xScales.push_back("11-20");
        xScales.push_back("11-21");
        xScales.push_back("11-22");

        INT_VEC yScales;
        yScales.reserve(10);
        yScales.push_back(200);
        yScales.push_back(130);
        yScales.push_back(3456);
        yScales.push_back(2345);
        yScales.push_back(1320);
        yScales.push_back(30);
        yScales.push_back(2200);
        yScales.push_back(1330);
        yScales.push_back(3330);
        yScales.push_back(332);
        yScales.push_back(788);
        yScales.push_back(200);
        yScales.push_back(13890);
        yScales.push_back(200);

        TinyTrendlineDiagram* pt = new TinyTrendlineDiagram(
                "trendline_test.png", 800, 250);
        pt->SetTitle("Trend of Latency (the middle network latency is the value of 0 coordinate)");
        pt->SetLabels(xScales);
        pt->SetValues(yScales);

        pt->Draw();
        pt->WriteImage();
        delete pt;
    }

    {
        STR_VEC xScales;
        xScales.push_back("San Jose");
        xScales.push_back("Denver");
        xScales.push_back("Virginia");
        xScales.push_back("London");
        xScales.push_back("tokyo");
        xScales.push_back("Hon kong");
        xScales.push_back("Melbourne");
        xScales.push_back("Mumbai");

        INT_VEC yScales;
        yScales.push_back(4800);
        yScales.push_back(3008);
        yScales.push_back(100);
        yScales.push_back(20);
        yScales.push_back(2000);
        yScales.push_back(178);
        yScales.push_back(258);
        yScales.push_back(1789);

        TinyDatacenterDiagram* pd = new TinyDatacenterDiagram(
                "datacenter_usage.png", 800, 600);
        pd->SetTitle("Daily active users distribution among the data centers");
        pd->SetLabels(xScales);
        pd->SetValues(yScales);
        pd->Draw();
        pd->WriteImage();
        delete pd;
    }
    return 0;
}
