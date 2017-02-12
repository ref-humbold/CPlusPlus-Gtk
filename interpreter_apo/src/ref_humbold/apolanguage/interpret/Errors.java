package ref_humbold.apolanguage.interpret;

/**
Klasa rzucajaca wyjatki podczas wykonywania programu.
Wywolanie wyjatku powoduje natychmiastowe zakonczenie pracy interpretera.
*/
class Errors
{
    private static String[] aritTypes = {"Division by zero.", "Argument is not a number."};
    private static String[] memTypes = {"Out of memory.", "Address is not alligned to a word.", "Number to store not in a byte."};
    private static String[] symTypes = {"Cannot change variable \'zero\'.", "Not existing instruction.", "Too few arguments.", "Invalid symbols in variable name.\tVariableList contain lower case only."};
    private static String[] lblTypes = {"Label not found.", "Duplicated label.", "VariableList and labels cannot have the same name.", "Invalid symbols in label name.\tLabels contain lower case only."};

    /**
    Wypisuje komunikat o wystapieniu wyjatku zwiazanego z operacjami arytmetycznymi.
    @param x szczegolowy typ wyjatku
    @param curline wiersz programu, w ktorym nastapil wyjatek
    */
    public static void aritErr(int x, int curline)
    {
        System.err.println("error>> ArithmeticError at line "+curline+"\t"+aritTypes[x]);
        System.exit(0);
    }

    /**
    Wypisuje komunikat o wystapieniu wyjatku zwiazanego z operacjami na pamieci.
    @param x szczegolowy typ wyjatku
    @param curline wiersz programu, w ktorym nastapil wyjatek
    */
    public static void memErr(int x, int curline)
    {
        System.err.println("error>> MemoryError at line "+curline+"\t"+memTypes[x]);
        System.exit(0);
    }

    /**
    Wypisuje komunikat o wystapieniu wyjatku zwiazanego z instrukcjami badz zmiennymi.
    @param x szczegolowy typ wyjatku
    @param curline wiersz programu, w ktorym nastapil wyjatek
    */
    public static void symErr(int x, int curline)
    {
        System.err.println("error>> SymbolError at line "+curline+"\t"+symTypes[x]);
        System.exit(0);
    }

    /**
    Wypisuje komunikat o wystapieniu wyjatku zwiazanego z etykietami.
    @param x szczegolowy typ wyjatku
    @param curline wiersz programu, w ktorym nastapil wyjatek
    */
    public static void lblErr(int x, int curline)
    {
        System.err.println("error>> LabelError at line "+curline+"\t"+lblTypes[x]);
        System.exit(0);
    }
}
