<?php

public class Token{
        static $BooleanLiteral= 1;
        static $EOF= 2;
        static $Identifier= 3;
        static $Keyword= 4;
        static $NullLiteral= 5;
        static $NumericLiteral= 6;
        static $Punctuator= 7;
        static $StringLiteral= 8;
        static $RegularExpression= 9;
        static $Template= 10;
}

public class CodeExecutionContext{
  public $Token;
  public    $TokenName,
  public    $FnExprTokens,
    public   $Syntax,
    public $PlaceHolders,
    public  $Messages,
      public $Regex,
      public $source,
      public $strict,
      public $index,
      public $lineNumber,
      public $lineStart,
      public $hasLineTerminator,
      public $lastIndex,
      public $lastLineNumber,
      public $lastLineStart,
      public $startIndex,
      public $startLineNumber,
      public $startLineStart,
      public $scanning,
      public $length,
      public $lookahead,
      public $state,
      public $extra,
      public $isBindingElement,
      public $isAssignmentTarget,
      public $firstCoverInitializedNameError;


      public function CreateExecutionContext(){
      $z1=json_decode (" ['(', '{', '[', 'in', 'typeof', 'instanceof', 'new',
                        'return', 'case', 'delete', 'throw', 'void',
                        // assignment operators
                        '=', '+=', '-=', '*=', '/=', '%=', '<<=', '>>=', '>>>=',
                        '&=', '|=', '^=', ',',
                        // binary/unary operators
                        '+', '-', '*', '/', '%', '++', '--', '<<', '>>', '>>>', '&',
                        '|', '^', '!', '~', '&&', '||', '?', ':', '===', '==', '>=',
                        '<=', '<', '>', '!=', '!==']");
      }

}
