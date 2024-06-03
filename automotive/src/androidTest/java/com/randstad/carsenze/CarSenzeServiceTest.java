package com.randstad.carsenze;

import static com.randstad.carsenze.CarSenzeService.memoryInfo;
import static org.junit.Assert.*;

import org.junit.Test;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class CarSenzeServiceTest {

    static {
        System.loadLibrary("carsenze");
    }
   // TestClass myTest = new TestClass();
    @Test
    public void addition_isCorrect() {
        assertEquals(4, 2 + 2);

    }
    @Test
    public void getCpuStats_test(){
       // System.out.println(memoryInfo());
        assertEquals("MEM 54GB", memoryInfo());
    }
}