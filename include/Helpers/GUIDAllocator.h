#pragma once

class GUID_Allocator
{
    public:
        static int getNewUniqueGUID()
        {
            return currentGUID++;
        }
        
    private:
        static int currentGUID;

};