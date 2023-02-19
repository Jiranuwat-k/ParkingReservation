#ifndef PARKINGADVICE_H
#define PARKINGADVICE_H
    struct parkingadvice
    {
        int  maxcatetory;
        char catetory[10][256];
        int  parkingnear[10][3];
    };
    char catetory[][125] = {
        "CAFE & RESTAURANTS","BEAUTY & WELLNESS",
        "FASHION & ACCESSORIES","BOOK, STATIONERY & LIFESTYLE",
        "BANK & INSURANCE","GADGET & TECHNOLOG",
        "SERVICES & OTHER"
    };
    struct parkingadvice LEVEL1 = {
                            .maxcatetory = 4,
                            .catetory = {
                                "CAFE & RESTAURANTS",
                                "BEAUTY & WELLNESS",
                                "SERVICES & OTHER",
                                "FASHION & ACCESSORIES"
                            },
                            .parkingnear = {
                                {3,2,4},
                                {3,4,2},
                                {3,4,2},
                                {3,4,2}
                            }
                        };
    struct parkingadvice LEVEL2 = {
                            .maxcatetory = 7,
                            .catetory = {
                                "GADGET & TECHNOLOG",
                                "FASHION & ACCESSORIES",
                                "BEAUTY & WELLNESS",
                                "BOOK, STATIONERY & LIFESTYLE",
                                "SERVICES & OTHER",
                                "BANK & INSURANCE",
                                "CAFE & RESTAURANTS"
                            },
                            .parkingnear = {
                                {3,2,4},
                                {4,3,2},
                                {3,4,2},
                                {4,3,2},
                                {4,3,2},
                                {4,3,2},
                                {4,3,2}
                            }
                        };
    struct parkingadvice LEVEL3 = {
                            .maxcatetory = 4,
                            .catetory = {
                                "BANK & INSURAN",
                                "CAFF’& RESTAURANT",
                                "BOOK, STATIONERY & LIFESTYLE",
                                "SERVICES & OTHER"
                            },
                            .parkingnear ={
                                {3,4,2},
                                {3,4,2},
                                {3,2,4},
                                {4,3,2}
                            }
                        };
    struct parkingadvice LEVEL4 = {
                            .maxcatetory = 1,
                            .catetory = {
                                "SERVICES & OTHER"
                            },
                            .parkingnear = {
                                {3,4,2}
                            }
                        };
#endif