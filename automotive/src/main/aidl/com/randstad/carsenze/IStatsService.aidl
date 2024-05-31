// IStatsService.aidl
package com.randstad.carsenze;

// Declare any non-default types here with import statements

interface IStatsService {
    /**
     * Demonstrates some basic types that you can use as parameters
     * and return values in AIDL.
     */
    String getCpuStats();
    String getMemoryStats();
    String getNetworkStats();
}