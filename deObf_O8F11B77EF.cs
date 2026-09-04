{
	internal class String // # ** internal class O8F11B77EF
	{
		internal static String Empty; // 0x0
		internal static String WhiteSpace; // 0x8
		private static readonly System.UInt16 NullHash; // 0x10
		private readonly System.Char[] Items; // 0x10

		internal System.Char Chars { get; }
		internal System.Int32 Length { get; }

		// RVA: 0x1A26CD0
		public override System.Boolean Equals(System.Object obj) { }

		// RVA: 0x1A2630C
		internal static String FromCharArray(System.Char[] chars) { }

		// RVA: 0x1A26E48
		private static System.Char ToLower(System.Char c) { }

		// RVA: 0x1A26DF0
		private System.Void .ctor(System.Char[] value) { }

		// RVA: 0x1A27000
		internal String Concat(String strA, String strB) { }

		// RVA: 0x1A27194
		internal System.Char[] ToCharArray() { }

		// RVA: 0x1A272C4
		internal String[] Split(System.Char separator) { }

		// RVA: 0x1A27608
		public static String Format(String format, String arg0) { }

		// RVA: 0x1A276A4
		internal System.Int32 IndexOf(String value, StringComparison comparisonType) { }

		// RVA: 0x1A277BC
		internal String Replace(String oldValue, String newValue) { }

		// RVA: 0x1A27EE0
		internal static System.Boolean IsNullOrEmpty(String value) { }

		// RVA: 0x1A27F64
		internal System.Boolean StartsWith(String value) { }

		// RVA: 0x1A27F88
		internal static String FromChar(System.Char c) { }

		// RVA: 0x1A28128
		internal System.Boolean Contains(String value) { }

		// RVA: 0x1A27D2C
		private String SplitInternal(System.Int32 count, String separator, StringSplitOptions options) { }

		// RVA: 0x1A25E3C
		internal static String Concat(String str0, String str1, String str2) { }

		// RVA: 0x1A253B8
		internal System.String ToString() { }

		// RVA: 0x1A281D4
		internal System.Boolean ContainsAll(String value) { }

		// RVA: 0x1A252B8
		internal System.Void .ctor(System.Char c, System.Int32 count) { }

		// RVA: 0x1A282F4
		internal String Substring(System.Int32 startIndex) { }

		// RVA: 0x1A283C8
		private static System.Void .cctor() { }

		// RVA: 0x1A28580
		public override System.Int32 GetHashCode() { }

		// RVA: 0x1A27A08
		internal String Replace(String oldValue, String newValue) { }

		// RVA: 0x1A28598
		internal String Remove(System.Int32 startIndex, System.Int32 count) { }

		// RVA: 0x1A28794
		internal static String Concat(String str0, String str1, String str2, String str3) { }

		// RVA: 0x1A261BC
		internal System.Int32 PadRight(System.Int32 totalWidth) { }

		// RVA: 0x1A28A14
		internal System.Int32 IndexOf(String value) { }

		// RVA: 0x1A28AF0
		public static String Join(String separator, String[] values) { }

		// RVA: 0x1A28B68
		private static System.Char ToUpper(System.Char c) { }

		// RVA: 0x1A255F8
		public static System.Boolean Equals(String a, String b) { }

		// RVA: 0x1A275EC
		internal String Concat(String str) { }

		// RVA: 0x1A28BC8
		public static String Join(String separator, System.Collections.Generic.IEnumerable<String> values) { }

		// RVA: 0x1A28C64
		internal System.Boolean Contains(System.Char value) { }

		// RVA: 0x1A28D18
		public static System.Int32 Compare(String strA, String strB) { }

		// RVA: 0x1A26EA8
		private System.Void .ctor(System.Char[] value, System.Int32 startIndex) { }

		// RVA: 0x1A27124
		private System.Void .ctor(System.Int32 count) { }

		// RVA: 0x1A28DEC
		internal static String Concat(System.Object arg0) { }

		// RVA: 0x1A26D68
		private static System.Boolean Compare(String strA, String strB) { }

		// RVA: 0x1A28298
		internal System.Int32 GetHashCode() { }

		// RVA: 0x1A25A64
		internal System.Void .ctor(System.Char c) { }

		// RVA: 0x1A28E5C
		internal static String CreateFromCharArray(System.Char[] chars) { }

		// RVA: 0x1A27F80
		internal System.Int32 IndexOf(String value, System.Int32 startIndex) { }

		// RVA: 0x1A28EFC
		internal static String Concat(String str0, String str1) { }

		// RVA: 0x1A284D4
		private System.Void .ctor() { }

		// RVA: 0x1A25734
		internal static String Trim(String str) { }

		// RVA: 0x1A28F60
		internal String ToUpper() { }

		// RVA: 0x1A29018
		internal System.Int32 LastIndexOf(System.Char value) { }

		// RVA: 0x1A261D4
		internal System.Char get_Chars(System.Int32 index) { }

		// RVA: 0x1A253D4
		public static String Concat(String str0, String str1) { }

		// RVA: 0x1A290B8
		public static String Concat(String str0, String str1) { }

		// RVA: 0x1A257CC
		public static System.Boolean op_Inequality(String a, String b) { }
	}
}
