#pragma once
#include <map>
#include "../../application/structs/CheckData.h"


class CheckRepository
{
public:
    CheckRepository();
    CheckData SetChecked(int checkId);
    CheckData GetCheck(int checkId);
    std::map<int, CheckData> GetChecks();

private:
    std::map<int, CheckData> _checkData;
};
