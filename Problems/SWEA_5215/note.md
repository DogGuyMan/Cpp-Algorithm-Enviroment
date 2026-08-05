DP[0][CAL = 0] = (VAL = 0);
DP[1][CAL = 0] = (VAL = 0);
DP[2][CAL = 0] = (VAL = 0);
DP[3][CAL = 0] = (VAL = 0);
DP[4][CAL = 0] = (VAL = 0);
DP[5][CAL = 0] = (VAL = 0);

DP[][1] = -INF
DP[1][200] = 100
DP[2][200] = 100
DP[3][200] = 100
DP[4][200] = 100
DP[5][200] = 100

DP[1][300] = INF
DP[2][300] = 250
DP[3][300] = 250
DP[4][300] = 250
DP[5][300] = 250

DP[1][400] = INF
DP[2][400] = INF
DP[3][400] = 400
DP[4][400] = 400
DP[5][400] = 400

DP[1][500] = INF
DP[2][500] = 350 = DO[2][200 + ingre[2].CAL] = DP[2-1][200] + ingre[2].VAL
DP[3][500] = 350 = DP[3][100 + ingre[3].CAL] = DP[3][100] == INF
DP[4][500] = 400 = DP[4][CAL = 0 + ingre[2].CAL = 500] = DP[4][CAL = 0] = (VAL = 0) + ingre[4].VAL;
DP[5][500] = 400

DP[cur_depth][cur_cal] = DP[cur_depth-1][cur_cal];
if(cur_cal - ingre[cur_depth].CAL >= 0 && DP[cur_cal - ingre[cur_depth].CAL] != -INF) 
{
    DP[cur_depth][cur_cal] = min(
        DP[cur_depth][cur_cal],
        DP[cur_depth-1][cur_cal - ingre[cur_depth].CAL] + ingre[cur_depth-1].VAL
    );
}