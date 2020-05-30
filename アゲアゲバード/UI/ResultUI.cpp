#include "ResultUI.h"
#include "../Manager/UIManager.h"
void ResultUI::LoadFile()
{
	UIManager::Instance()->GetUI();
}

void ResultUI::Init()
{
	// š ¼‚ª’Ç‰Á‚µ‚½‚â‚Â
	m_csv->GetInstance()->LoadData("RankingData.txt");
	m_score_table = *m_csv->GetInstance()->GetParam("Ranking");

	// geter‚±‚±

	m_score_table.push_back(m_timefont);
	m_csv->WriteData("RankingData.txt", m_score_table);
	/*for (int i = 0; i < m_score_table[i].size(); i++)
	{
		m_no1[20] = m_score_table[0][i];
		m_no2[20] = m_score_table[1][i];
		m_no3[20] = m_score_table[2][i];
	}*/
}

void ResultUI::Draw()
{
	DrawFont(1000, 0, m_timefont, FontSize::Regular, FontColor::Red);
	DrawFont(1000, 0, m_timefont, FontSize::Regular, FontColor::Red);
	DrawFont(1000, 0, m_timefont, FontSize::Regular, FontColor::Red);
}

void ResultUI::ReleaseTex()
{

}
