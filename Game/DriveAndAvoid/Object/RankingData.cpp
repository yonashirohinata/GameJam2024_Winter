#include "RankingData.h"
#include <stdio.h>
#include <string.h>

RankingData::RankingData()
{
	for (int i = 0; i < 6; i++)
	{
		score[i] = NULL;
		rank[i] = NULL;
		for (int j = 0; j < 15; j++)
		{
			name[i][j] = '\0';
		}
	}
}

RankingData::~RankingData()
{

}

//����������
void RankingData::Initialize()
{
	//�����L���O�f�[�^�̓ǂݍ���
	FILE* fp = nullptr;

	//�t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/ranking_data.csv���J���܂���ł���\n");
	}
}