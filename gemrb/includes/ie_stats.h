#ifndef IE_STATS_H
#define IE_STATS_H

//EA values
#define INANIMATE   			1
#define PC  					2
#define FAMILIAR				3
#define ALLY					4
#define CONTROLLED  			5
#define CHARMED 				6
#define GOODBUTRED  			28
#define GOODBUTBLUE 			29
#define GOODCUTOFF  			30
#define NOTGOOD 				31
#define ANYTHING				126
#define NEUTRAL 				128
#define NOTEVIL 				199
#define EVILCUTOFF  			200
#define EVILBUTGREEN	201
#define EVILBUTBLUE 			202
#define ENEMY   				255

//state bits (IE_STATE)
#define STATE_DEAD  2048

//stats
#define IE_HITPOINTS 0
#define IE_MAXHITPOINTS	1
#define IE_ARMORCLASS	2
#define IE_ACCRUSHINGMOD	3
#define IE_ACMISSILEMOD	4
#define IE_ACPIERCINGMOD	5
#define IE_ACSLASHINGMOD	6
#define IE_THAC0		7
#define IE_NUMBEROFATTACKS	8
#define IE_SAVEVSDEATH	9
#define IE_SAVEVSWANDS	10
#define IE_SAVEVSPOLY	11
#define IE_SAVEVSBREATH	12
#define IE_SAVEVSSPELL	13
#define IE_RESISTFIRE	14
#define IE_RESISTCOLD	15
#define IE_RESISTELECTRICITY	16
#define IE_RESISTACID	17
#define IE_RESISTMAGIC	18
#define IE_RESISTMAGICFIRE	19
#define IE_RESISTMAGICCOLD	20
#define IE_RESISTSLASHING	21
#define IE_RESISTCRUSHING	22
#define IE_RESISTPIERCING	23
#define IE_RESISTMISSILE	24
#define IE_LORE		25
#define IE_LOCKPICKING	26
#define IE_STEALTH		27
#define IE_TRAPS		28
#define IE_PICKPOCKET	29
#define IE_FATIGUE		30
#define IE_INTOXICATION	31
#define IE_LUCK		32
#define IE_TRACKING	33
#define IE_LEVEL		34
#define IE_SEX		35
#define IE_STR		36
#define IE_STREXTRA	37
#define IE_INT		38
#define IE_WIS		39
#define IE_DEX		40
#define IE_CON		41
#define IE_CHR		42
#define IE_XPVALUE		43
#define IE_XP		44
#define IE_GOLD		45
#define IE_MORALEBREAK	46
#define IE_MORALERECOVERYTIME	47
#define IE_REPUTATION	48
#define IE_HATEDRACE	49
#define IE_DAMAGEBONUS	50
#define IE_SPELLFAILUREMAGE	51
#define IE_SPELLFAILUREPRIEST	52
#define IE_SPELLDURATIONMODMAGE	53
#define IE_SPELLDURATIONMODPRIEST	54
#define IE_TURNUNDEADLEVEL	55
#define IE_BACKSTABDAMAGEMULTIPLIER	56
#define IE_LAYONHANDSAMOUNT	57
#define IE_HELD 		   58
#define IE_POLYMORPHED     59
#define IE_TRANSLUCENT     60
#define IE_IDENTIFYMODE    61
#define IE_ENTANGLE	62
#define IE_SANCTUARY	63
#define IE_MINORGLOBE	64
#define IE_SHIELDGLOBE	65
#define IE_GREASE		66
#define IE_WEB		67
#define IE_LEVEL2   	   68
#define IE_LEVEL3   	   69
#define IE_CasterHold	70
#define IE_ENCUMBERANCE    71
#define IE_MISSILETHAC0BONUS	  72  
#define IE_MAGICDAMAGERESISTANCE  73
#define IE_RESISTPOISON 	 74
#define IE_DONOTJUMP		  75
#define IE_AURACLEANSING	  76
#define IE_MENTALSPEED  	  77
#define IE_PHYSICALSPEED	  78
#define IE_CASTINGLEVELBONUSMAGE	79
#define IE_CASTINGLEVELBONUSCLERIC  80
#define IE_SEEINVISIBLE 			81
#define IE_IGNOREDIALOGPAUSE		82
#define IE_MINHITPOINTS		 83
#define IE_THAC0BONUSRIGHT  		84
#define IE_THAC0BONUSLEFT   		85
#define IE_DAMAGEBONUSRIGHT 		86
#define IE_DAMAGEBONUSLEFT  		87
#define IE_STONESKINS  88
#define IE_PROFICIENCYBASTARDSWORD		89
#define IE_PROFICIENCYLONGSWORD		90
#define IE_PROFICIENCYSHORTSWORD		91
#define IE_PROFICIENCYAXE			92			
#define IE_PROFICIENCYTWOHANDEDSWORD	93
#define IE_PROFICIENCYKATANA		94
#define IE_PROFICIENCYSCIMITARWAKISASHININJATO	95
#define IE_PROFICIENCYDAGGER		96
#define IE_PROFICIENCYWARHAMMER	97
#define IE_PROFICIENCYSPEAR	98
#define IE_PROFICIENCYHALBERD		99			
#define IE_PROFICIENCYFLAILMORNINGSTAR	100
#define IE_PROFICIENCYMACE			101			
#define IE_PROFICIENCYQUARTERSTAFF		102		
#define IE_PROFICIENCYCROSSBOW			103		
#define IE_PROFICIENCYLONGBOW			104		
#define IE_PROFICIENCYSHORTBOW			105		
#define IE_PROFICIENCYDART				106
#define IE_PROFICIENCYSLING				107	
#define IE_PROFICIENCYBLACKJACK			108	
#define IE_PROFICIENCYGUN				109		
#define IE_PROFICIENCYMARTIALARTS			110	
#define IE_PROFICIENCY2HANDED				   111 
#define IE_PROFICIENCYSWORDANDSHIELD			112
#define IE_PROFICIENCYSINGLEWEAPON			113	
#define IE_PROFICIENCY2WEAPON				   114  			
#define IE_EXTRAPROFICIENCY1 		 115
#define IE_EXTRAPROFICIENCY2 		 116
#define IE_EXTRAPROFICIENCY3 		 117
#define IE_EXTRAPROFICIENCY4 		 118
#define IE_EXTRAPROFICIENCY5 		 119
#define IE_EXTRAPROFICIENCY6 		 120
#define IE_EXTRAPROFICIENCY7 		 121
#define IE_EXTRAPROFICIENCY8 		 122
#define IE_EXTRAPROFICIENCY9 		 123
#define IE_EXTRAPROFICIENCY10 		 124
#define IE_EXTRAPROFICIENCY11 		 125
#define IE_EXTRAPROFICIENCY12 		 126
#define IE_EXTRAPROFICIENCY13 		 127
#define IE_EXTRAPROFICIENCY14 		 128
#define IE_EXTRAPROFICIENCY15 		 129
#define IE_EXTRAPROFICIENCY16 		 130
#define IE_EXTRAPROFICIENCY17 		 131
#define IE_EXTRAPROFICIENCY18 		 132
#define IE_EXTRAPROFICIENCY19 		 133
#define IE_EXTRAPROFICIENCY20 		 134
#define IE_HIDEINSHADOWS			  135
#define IE_DETECTILLUSIONS  		  136
#define IE_SETTRAPS 				  137
#define IE_PUPPETMASTERID   		  138
#define IE_PUPPETMASTERTYPE 		  139
#define IE_PUPPETTYPE   			  140
#define IE_PUPPETID 				  141
#define IE_CHECKFORBERSERK  		  142
#define IE_BERSERKSTAGE1			  143
#define IE_BERSERKSTAGE2			  144
#define IE_DAMAGELUCK   			  145
#define IE_CRITICALHITBONUS 		  146
#define IE_VISUALRANGE  			  147
#define IE_EXPLORE  				  148
#define IE_THRULLCHARM  			  149
#define IE_SUMMONDISABLE			  150
#define IE_HITBONUS 				  151    
#define IE_KIT  					  152 
#define IE_FORCESURGE   			  153
#define IE_SURGEMOD 				  154
#define IE_IMPROVEDHASTE			  155
#define IE_SCRIPTINGSTATE1  		  156
#define IE_SCRIPTINGSTATE2  		  157
#define IE_SCRIPTINGSTATE3  		  158
#define IE_SCRIPTINGSTATE4  		  159
#define IE_SCRIPTINGSTATE5  		  160
#define IE_SCRIPTINGSTATE6  		  161
#define IE_SCRIPTINGSTATE7  	162   
#define IE_SCRIPTINGSTATE8  	163
#define IE_SCRIPTINGSTATE9  	164
#define IE_SCRIPTINGSTATE10 	165
#define IE_MELEETHAC0		166
#define IE_MELEEDAMAGE		167
#define IE_MISSILEDAMAGE	168
#define IE_NOCIRCLE		169
#define IE_FISTTHAC0		170
#define IE_FISTDAMAGE		171
#define IE_TITLE1		172
#define IE_TITLE2		173
#define IE_DISABLEOVERLAY	174
#define IE_DISABLEBACKSTAB	175
#define IE_STONESKINSGOLEM	199
#define IE_LEVELDRAIN		200
#define IE_RACE			201
#define IE_CLASS		202
#define IE_GENERAL		203
#define IE_EA			204
#define IE_SPECIFIC		205
//GemRB Specific Defines
#define IE_ANIMATION_ID		206
#define IE_STATE_ID		207
#define IE_METAL_COLOR		208
#define IE_MINOR_COLOR		209
#define IE_MAJOR_COLOR		210
#define IE_SKIN_COLOR		211
#define IE_LEATHER_COLOR	212
#define IE_ARMOR_COLOR		213
#define IE_HAIR_COLOR		214
#define IE_MC_FLAGS		215
#define IE_TALKCOUNT		216
#define IE_ALIGNMENT		217
#define IE_UNSELECTABLE		218
#define IE_ARMOR_TYPE		219
#define IE_TEAM			220
#define IE_FACTION		221
#define IE_SUBRACE		222

#endif
