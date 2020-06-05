#include "ResultUI.h"
#include "../Manager/UIManager.h"

void ResultUI::Init()
{
	m_csv->GetInstance()->LoadData("RankingData.txt");
	// š ¼‚ª’Ç‰Á‚µ‚½‚â‚Â
	m_score_table = *m_csv->GetInstance()->GetParam("Ranking");

	m_score_table.push_back(UIManager::Instance()->GetGameUI()->GetUIInfo()->m_timefont);
	m_csv->GetInstance()->WriteData("RankingData.txt", m_score_table);

	m_csv->GetInstance()->LoadData("RankingData.txt");
	m_score_table = *m_csv->GetInstance()->GetParam("Ranking");
	

	for (int j = 0; j < m_score_table[0].size(); j++)
	{
		m_ranking.first[j] = m_score_table[0][j];
		m_ranking.second[j] = m_score_table[1][j];
		m_ranking.third[j] = m_score_table[2][j];
	}
}

void ResultUI::Draw()
{
	DrawFont(750, 370, m_ranking.first, FontSize::Large, FontColor::Red);
	DrawFont(750, 540, m_ranking.second, FontSize::Large, FontColor::Red);
	DrawFont(750, 710, m_ranking.third, FontSize::Large, FontColor::Red);
}

void ResultUI::ReleaseTex()
{

}
