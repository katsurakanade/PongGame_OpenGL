#include "Resource.h"

bool Resource::Hitcheck(glm::vec3 line_pos_0, glm::vec3 line_pos_1, glm::vec3 circle_pos, float radius) {

	int		dx, dy;
	int		t0, t1;
	float	t;
	bool	ans;

	ans = false;

	// �����̒[�_0�Ɖ~�̒��S�܂ł̋����Ń`�F�b�N
	dx = line_pos_0.x - circle_pos.x;
	dy = line_pos_0.y - circle_pos.y;
	if ((dx * dx + dy * dy) <= radius * radius) ans = true;//������

	// �����̒[�_1�Ɖ~�̒��S�܂ł̋����Ń`�F�b�N
	dx = line_pos_1.x - circle_pos.x;
	dy = line_pos_1.y - circle_pos.y;
	if ((dx * dx + dy * dy) <= radius * radius) ans = true;//������

	// ��8�̏����@t0/t1�̌v�Z�p
	t0 = (circle_pos.x - line_pos_0.x) * (line_pos_1.x - line_pos_0.x) + (circle_pos.y - line_pos_0.y) * (line_pos_1.y - line_pos_0.y);
	t1 = (line_pos_1.x - line_pos_0.x) * (line_pos_1.x - line_pos_0.x) + (line_pos_1.y - line_pos_0.y) * (line_pos_1.y - line_pos_0.y);

	int			g_Vx, g_Vy;

	if (t1 != 0)	// t1��0���ƃG���[�ɂȂ�̂ŔO�̂��߃`�F�b�N
	{
		t = (float)t0 / t1; //��8

		if (0.0f <= t && t <= 1.0f) {// 0<= t <= 1 �Ȃ炠����̉\��
			//��9 t�����܂�ƒ�����̌�_�ig_Vx, g_Vy�j������B
			//�i��ʍ��W�Ȃ̂Ő����^�փL���X�g���Ċi�[�j
			g_Vx = (int)((line_pos_1.x - line_pos_0.x) * t + line_pos_0.x);
			g_Vy = (int)((line_pos_1.y - line_pos_0.y) * t + line_pos_0.y);

			//�ŒZ�����̌�_�Ɖ~�̒��S�Ƃ̋��������a��菬������΂�����
			dx = circle_pos.x - g_Vx;
			dy = circle_pos.y - g_Vy;

			if ((dx * dx + dy * dy) <= radius * radius) ans = true;//������
		}
	}
	return ans;
}