#include "ResultUI.h"
#include "../Manager/UIManager.h"

void ResultUI::Init()
{
	// š ¼‚ª’Ç‰Á‚µ‚½‚â‚Â
	m_csv->GetInstance()->LoadData("RankingData.txt");
	m_score_table = *m_csv->GetInstance()->GetParam("Ranking");

	m_score_table.push_back(UIManager::Instance()->GetGameUI()->GetUIInfo()->m_timefont);
	m_csv->WriteData("RankingData.txt", m_score_table);
	for (int j = 0; j < m_score_table[0].size(); j++)
	{
		m_ranking.first[j] = m_score_table[0][j];
		m_ranking.second[j] = m_score_table[1][j];
		m_ranking.third[j] = m_score_table[2][j];
	}
}

void ResultUI::Draw()
{
	DrawFont(1000, 0, m_no1, FontSize::Regular, FontColor::Red);
	DrawFont(1000, 0, m_no2, FontSize::Regular, FontColor::Red);
	DrawFont(1000, 0, m_no3, FontSize::Regular, FontColor::Red);
}

void ResultUI::ReleaseTex()
{

}
