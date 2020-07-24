package ekutt.example.imageconverter;

import android.content.Context;

import androidx.test.platform.app.InstrumentationRegistry;
import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.*;

/**
 * Instrumented test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class ImageConvertInstrumentedTest {
    ImageConverter calc = new ImageConverter();
    @Test
    public void useAppContext() {
        // Context of the app under test.
        Context appContext = InstrumentationRegistry.getInstrumentation().getTargetContext();
        assertEquals("ekutt.example.gpacalculator", appContext.getPackageName());
    }

    @Test
    public void grade_addition_isCorrect()
    {
        calc.addGrade("James", 3.0f, 4);
        assertEquals(calc.calculateGPAs().get(0).name, "James");
        assertEquals(calc.calculateGPAs().get(0).totalCredits, 4);
    }

    @Test
    public void gpa_calculation_isCorrect()
    {
        calc.addGrade("James", 3.0f, 4);
        assertEquals(calc.calculateGPAs().size(), 1);
        assertEquals(Double.doubleToLongBits(calc.calculateGPAs().get(0).gpa),
                Double.doubleToLongBits(3.0f));
    }

    @Test
    public void clear_data_isCorrect()
    {
        calc.addGrade("James", 3.0f, 4);
        calc.clearData();
        assertEquals(calc.calculateGPAs().size(), 0);
    }
}