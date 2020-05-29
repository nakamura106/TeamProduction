#include "ResultUI.h"
#include "../Manager/UIManager.h"
void ResultUI::LoadFile()
{
	UIManager::Instance()->GetUI();
	m_ranking.push_back(std::stof(m_timefont));

	std::sort(m_ranking.begin(), m_ranking.end());

	m_csv->WriteData("RankingData.txt", m_ranking);
}

void ResultUI::Init()
{
	m_csv->GetInstance()->LoadData("RankingData.txt");
	m_strvec = *m_csv->GetInstance()->GetParam("Ranking");

	m_no1[10] = std::stof(m_strvec[0]);
	m_no2[10] = std::stof(m_strvec[1]);
	m_no3[10] = std::stof(m_strvec[2]);

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
