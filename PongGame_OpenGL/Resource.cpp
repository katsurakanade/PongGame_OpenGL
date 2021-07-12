#include "Resource.h"

bool Resource::Hitcheck(glm::vec3 line_pos_0, glm::vec3 line_pos_1, glm::vec3 circle_pos, float radius) {

	int		dx, dy;
	int		t0, t1;
	float	t;
	bool	ans;

	ans = false;

	// 線分の端点0と円の中心までの距離でチェック
	dx = line_pos_0.x - circle_pos.x;
	dy = line_pos_0.y - circle_pos.y;
	if ((dx * dx + dy * dy) <= radius * radius) ans = true;//あたり

	// 線分の端点1と円の中心までの距離でチェック
	dx = line_pos_1.x - circle_pos.x;
	dy = line_pos_1.y - circle_pos.y;
	if ((dx * dx + dy * dy) <= radius * radius) ans = true;//あたり

	// ※8の準備　t0/t1の計算用
	t0 = (circle_pos.x - line_pos_0.x) * (line_pos_1.x - line_pos_0.x) + (circle_pos.y - line_pos_0.y) * (line_pos_1.y - line_pos_0.y);
	t1 = (line_pos_1.x - line_pos_0.x) * (line_pos_1.x - line_pos_0.x) + (line_pos_1.y - line_pos_0.y) * (line_pos_1.y - line_pos_0.y);

	int			g_Vx, g_Vy;

	if (t1 != 0)	// t1が0だとエラーになるので念のためチェック
	{
		t = (float)t0 / t1; //※8

		if (0.0f <= t && t <= 1.0f) {// 0<= t <= 1 ならあたりの可能性
			//※9 tが決まると直線上の交点（g_Vx, g_Vy）を作れる。
			//（画面座標なので整数型へキャストして格納）
			g_Vx = (int)((line_pos_1.x - line_pos_0.x) * t + line_pos_0.x);
			g_Vy = (int)((line_pos_1.y - line_pos_0.y) * t + line_pos_0.y);

			//最短距離の交点と円の中心との距離が半径より小さければあたり
			dx = circle_pos.x - g_Vx;
			dy = circle_pos.y - g_Vy;

			if ((dx * dx + dy * dy) <= radius * radius) ans = true;//あたり
		}
	}
	return ans;
}