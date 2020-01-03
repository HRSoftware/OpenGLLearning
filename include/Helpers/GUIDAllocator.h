#pragma once

class GUID_Allocator
{
    public:
        inline static int getNewUniqueGUID()
        {
            return currentGUID++;
        }
        
    private:
        inline static int currentGUID = 0;

};