#include <stdio.h>
#include <gsl/gsl_sf_log.h>
// Jedną z bibliotek numerycznych, jaką dodatkowo będziemy używać na zajęciach jest GSL (język C). Opis jak używać .
// Korzystając ze wsparcia dla wyświetlania reprezentacji liczb zmiennoprzecinkowych zobaczyć jak zmienia się cecha i mantysa dla coraz mniejszych liczb.
// Zaobserwować, kiedy matysa przestaje być znormalizowana i dlaczego?
// Kod załączyć jako komórka Markdown sformatowana jako C (link). Wynik także jako Markdown (kod albo fragment zrzutu ekranu).

int main(void)
{
    double x = 1.0;
    while (x > 0.0)
    {
        // binarna reprezentacja liczby x - używamy pointera żeby scastować
        // adress zmiennej x na typ unsigned long long - który ma ten sam rozmiar co double
        unsigned long long bits = *(unsigned long long *)&x;

        // mantysa - dla double 52 mniej znaczących bitów stąd 1uul << 52
        // ((1ull<<52)-1) - stworzenie maski zawierającej 52 bity od 0 do 51
        unsigned long long mantissa = bits & ((1ull << 52) - 1);

        // cecha - dla double 11 bardziej znaczących bitów stąd 1 << 11 
        int exponent = (bits >> 52) & ((1 << 11) - 1);

        // korygowanie wartości exponent, 1023 - zostało dodane do cechy w procesie konwersji
        // z systemu dziesiątkowego na binarny
        exponent -= 1023;
        printf("x: %g\tmantissa: %llu\texponent: %d\n", x, mantissa, exponent);
        x /= 2.0;
    }
    return 0;
}