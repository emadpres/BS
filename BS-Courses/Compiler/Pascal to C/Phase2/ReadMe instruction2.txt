1.tartibe shomarehaye $ beshekle zir ast:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
type :				standard_type						{printf("%s ",$<code>1);low=-1;high=-1;}
					|
					S_ARRAY								
					'['									
					NUM									{low = atoi($<code>3);} 
					S_DOTDOT							
					NUM									{high = atoi($<code>6);} <--- 6 !! action khate bala yedune be counter badia ezafe mikone :((
					']'									
					S_OF								
					standard_type						{printf("%s ",$<code>10);} <-- 10 !!
					
standard_type :		S_INTEGER 							{$<code>$=malloc(1+strlen($<code>1));
														strcpy( $<code>$, "int");}
					| S_REAL							{$<code>$=malloc(1+strlen($<code>1));
														strcpy( $<code>$, "float");}
				;
				
				
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
2.say kon injuri benvis :
					ID									{printf("void %s",$<code>1);}
					arguments							{printf("%s\n{\n",$<code>3);}
					
	bejaye inyeki ke baraye $<code>1 yeseri cherte jolosham ezafi miare:
					ID									
					arguments							{printf("void %s %s\n{\n",$<code>1,$<code>2);}
					
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
3. bazi vaghta $<code>1 ezafi chap mikone :
					ID									{printf(" %s ",$<code>1);}
	dar natije dasti khodet ezafiasho bezan:
														{getData($<code>1);printf(" %s ",data);}
	ke function getData ro balaye yac bezar:

		void getData(char *s)
		{
		int i=0;
		strcpy(data,s);
		for(;data[i]!='\0';i++)
			if( !(
				(data[i]<='Z' && data[i]>='A' )
					|| (data[i]<='z' && data[i]>='a' )
						|| (data[i]<='9' && data[i]>='0' ) ) )
						break;
						
		data[i]='\0';
		}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
4. tooye 2,3 bala, bahse ezafi chap kardan bud.. vali age az aghab zaidi chap mikard, Lex.l ro baresi kon..
ehtemalan yylval.code=yytext ro nazadi! nokte 1 ham tavajo kon !														