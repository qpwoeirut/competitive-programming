# import string
#
# with open("valid_words.txt") as f:
#     words = [line.strip() for line in f]
#
# moves = dict()
#
#
# def search(frag: str, old_possible_words: list[str]) -> tuple[bool, str]:
#     if frag in words:
#         return True, ""
#
#     possible_words = [word for word in old_possible_words if word.startswith(frag)]
#     if len(possible_words) == 0 and len(frag) >= 3:
#         return True, "challenge"
#
#     for c in string.ascii_lowercase:
#         result = search(frag + c, possible_words)
#         if result[0] is False:
#             moves[frag] = c
#             return True, c
#
#     # losing anyway, pick something where opponent might mess up
#     for c in string.ascii_lowercase:
#         if frag + c not in words and len([word for word in possible_words if word.startswith(frag + c)]) > 0:
#             moves[frag] = c
#             return False, c
#     moves[frag] = "e"
#     return False, "e"
#
#
# def simulate_opponent(frag: str):
#     if len([word for word in words if word.startswith(frag)]) == 0:
#         return
#
#     print(frag)
#     result = search(frag, words)
#     frag += result[1]
#
#     for c in string.ascii_lowercase:
#         simulate_opponent(frag + c)
#
#
# def main():
#     simulate_opponent("")
#     for c in string.ascii_lowercase:
#         simulate_opponent(c)
#     print(moves)
#     print(len(moves))
#
#
# if __name__ == "__main__":
#     main()

moves = {
    'aache': 'e', 'aach': 'e', 'aac': 'h', 'aa': 'c', 'abacu': 'e', 'abac': 'u', 'abaf': 'e', 'aba': 'f', 'abbes': 'e',
    'abbe': 's', 'abbo': 'e', 'abb': 'o', 'abdican': 'e', 'abdica': 'n', 'abdic': 'a', 'abdi': 'c', 'abdome': 'e',
    'abdom': 'e', 'abdo': 'm', 'abd': 'o', 'abho': 'e', 'abh': 'o', 'abidin': 'e', 'abidi': 'n', 'abidja': 'e',
    'abidj': 'a', 'abid': 'i', 'abi': 'd', 'abjec': 'e', 'abje': 'c', 'abjurin': 'e', 'abjuri': 'n', 'abjur': 'i',
    'abju': 'r', 'abj': 'e', 'ab': 'j', 'acaci': 'e', 'acac': 'i', 'academie': 'e', 'academi': 'e', 'academ': 'i',
    'acade': 'm', 'acad': 'e', 'aca': 'd', 'accedin': 'e', 'accedi': 'n', 'acced': 'i', 'acce': 'd', 'acciden': 'e',
    'accide': 'n', 'accid': 'e', 'acci': 'd', 'acclai': 'e', 'accla': 'i', 'acclimatin': 'e', 'acclimati': 'n',
    'acclimat': 'i', 'acclima': 't', 'acclim': 'a', 'accli': 'm', 'accl': 'a', 'acc': 'l', 'achievabl': 'e',
    'achievab': 'l', 'achieva': 'b', 'achiev': 'a', 'achie': 'v', 'achi': 'e', 'achromati': 'e', 'achromat': 'i',
    'achroma': 't', 'achrom': 'a', 'achro': 'm', 'achr': 'o', 'ach': 'i', 'ac': 'h', 'adelaid': 'e', 'adelai': 'd',
    'adela': 'i', 'adel': 'a', 'adep': 'e', 'ade': 'p', 'adherin': 'e', 'adheri': 'n', 'adher': 'i', 'adhe': 'r',
    'adh': 'e', 'ad': 'h', 'aegea': 'e', 'aege': 'a', 'aegi': 'e', 'aeg': 'i', 'aeratin': 'e', 'aerati': 'n',
    'aerato': 'e', 'aerat': 'o', 'aera': 't', 'aer': 'a', 'aeso': 'e', 'aes': 'o', 'ae': 'g', 'a': 'e', 'babblin': 'e',
    'babbli': 'n', 'babbl': 'i', 'babb': 'l', 'babie': 'e', 'babi': 'e', 'baboo': 'e', 'babo': 'o', 'bab': 'b',
    'ba': 'b', 'bb': 'e', 'b': 'b', 'cachin': 'e', 'cachi': 'n', 'cach': 'i', 'cac': 'h', 'caesa': 'e', 'caes': 'a',
    'cae': 's', 'ca': 'e', 'cb': 'e', 'c': 'b', 'dacc': 'e', 'dac': 'c', 'daedalu': 'e', 'daedal': 'u', 'daeda': 'l',
    'daed': 'a', 'daemo': 'e', 'daem': 'o', 'dae': 'd', 'da': 'e', 'db': 'e', 'd': 'b', 'eac': 'e', 'ea': 'c',
    'ebon': 'e', 'ebo': 'n', 'ebullienc': 'e', 'ebullien': 'c', 'ebullie': 'n', 'ebulli': 'e', 'ebull': 'i',
    'ebul': 'l', 'ebu': 'l', 'eb': 'u', 'eccentri': 'e', 'eccentr': 'i', 'eccent': 'r', 'eccen': 't', 'ecce': 'n',
    'ecc': 'e', 'echelo': 'e', 'echel': 'o', 'eche': 'l', 'ech': 'e', 'eclai': 'e', 'ecla': 'i', 'eclecti': 'e',
    'eclect': 'i', 'eclec': 't', 'ecle': 'c', 'eclipsin': 'e', 'eclipsi': 'n', 'eclips': 'i', 'eclip': 's', 'ecli': 'p',
    'ecl': 'i', 'ecologica': 'e', 'ecologic': 'a', 'ecologis': 'e', 'ecologi': 's', 'ecolog': 'i', 'ecolo': 'g',
    'ecol': 'o', 'eco': 'l', 'ecr': 'e', 'ec': 'r', 'eda': 'e', 'ed': 'a', 'eeril': 'e', 'eeri': 'l', 'eer': 'i',
    'ee': 'r', 'effacin': 'e', 'effaci': 'n', 'effac': 'i', 'effa': 'c', 'effec': 'e', 'effe': 'c', 'efficaciou': 'e',
    'efficacio': 'u', 'efficaci': 'o', 'efficac': 'i', 'effica': 'c', 'effic': 'a', 'effigie': 'e', 'effigi': 'e',
    'effig': 'i', 'effi': 'g', 'effloresc': 'e', 'efflores': 'c', 'efflore': 's', 'efflor': 'e', 'efflo': 'r',
    'effl': 'o', 'effor': 'e', 'effo': 'r', 'effronter': 'e', 'effronte': 'r', 'effront': 'e', 'effron': 't',
    'effro': 'n', 'effr': 'o', 'effusin': 'e', 'effusi': 'n', 'effus': 'i', 'effu': 's', 'eff': 'a', 'ef': 'f',
    'egalitaria': 'e', 'egalitari': 'a', 'egalitar': 'i', 'egalita': 'r', 'egalit': 'a', 'egali': 't', 'egal': 'i',
    'ega': 'l', 'eglantin': 'e', 'eglanti': 'n', 'eglant': 'i', 'eglan': 't', 'egla': 'n', 'egl': 'a', 'egregiou': 'e',
    'egregio': 'u', 'egregi': 'o', 'egreg': 'i', 'egres': 'e', 'egre': 's', 'egr': 'e', 'eg': 'r', 'eh': 'e', 'e': 'h',
    'fabe': 'e', 'fab': 'e', 'facad': 'e', 'faca': 'd', 'facia': 'e', 'faci': 'a', 'facsimil': 'e', 'facsimi': 'l',
    'facsim': 'i', 'facsi': 'm', 'facs': 'i', 'fac': 's', 'fahrenhei': 'e', 'fahrenhe': 'i', 'fahrenh': 'e',
    'fahren': 'h', 'fahre': 'n', 'fahr': 'e', 'fah': 'r', 'fa': 'h', 'fb': 'e', 'f': 'b', 'gae': 'e', 'ga': 'e',
    'gb': 'e', 'g': 'b', 'habakku': 'e', 'habakk': 'u', 'habak': 'k', 'haba': 'k', 'haberdashe': 'e', 'haberdash': 'e',
    'haberdas': 'h', 'haberda': 's', 'haberd': 'a', 'haber': 'd', 'habe': 'r', 'hab': 'e', 'hac': 'e', 'ha': 'c',
    'hb': 'e', 'h': 'b', 'iam': 'e', 'ia': 'm', 'iberia': 'e', 'iberi': 'a', 'iber': 'i', 'ibe': 'r', 'ibse': 'e',
    'ibs': 'e', 'ib': 'e', 'i': 'b', 'jacint': 'e', 'jacin': 't', 'jaci': 'n', 'jac': 'i', 'jad': 'e', 'ja': 'd',
    'jb': 'e', 'j': 'b', 'kabu': 'e', 'kab': 'u', 'kafk': 'e', 'kaf': 'k', 'kaise': 'e', 'kais': 'e', 'kai': 's',
    'ka': 'i', 'kbyt': 'e', 'kby': 't', 'kb': 'y', 'k': 'b', 'lacin': 'e', 'laci': 'n', 'laconi': 'e', 'lacon': 'i',
    'laco': 'n', 'lac': 'o', 'lafayett': 'e', 'lafayet': 't', 'lafaye': 't', 'lafay': 'e', 'lafa': 'y', 'laf': 'a',
    'lahor': 'e', 'laho': 'r', 'lah': 'o', 'la': 'h', 'lb': 'e', 'l': 'b', 'maastrich': 'e', 'maastric': 'h',
    'maastri': 'c', 'maastr': 'i', 'maast': 'r', 'maas': 't', 'maa': 's', 'ma': 'a', 'mbaban': 'e', 'mbaba': 'n',
    'mbab': 'a', 'mba': 'b', 'mb': 'a', 'm': 'b', 'nadi': 'e', 'nad': 'i', 'nairob': 'e', 'nairo': 'b', 'nair': 'o',
    'nai': 'r', 'nake': 'e', 'nak': 'e', 'namabl': 'e', 'namab': 'l', 'nama': 'b', 'nam': 'a', 'nanc': 'e', 'nan': 'c',
    'narcissu': 'e', 'narciss': 'u', 'narcis': 's', 'narci': 's', 'narcosi': 'e', 'narcos': 'i', 'narcoti': 'e',
    'narcot': 'i', 'narco': 's', 'narc': 'o', 'narratin': 'e', 'narrati': 'n', 'narrato': 'e', 'narrat': 'o',
    'narra': 't', 'narr': 'a', 'nar': 'c', 'na': 'r', 'nb': 'e', 'n': 'b', 'oase': 'e', 'oas': 'e', 'oa': 's', 'o': 'a',
    'pacifie': 'e', 'pacifi': 'e', 'pacif': 'i', 'paci': 'f', 'pac': 'i', 'pa': 'c', 'pb': 'e', 'p': 'b', 'qata': 'e',
    'qat': 'a', 'qa': 't', 'q': 'a', 'raba': 'e', 'rab': 'a', 'raccoo': 'e', 'racco': 'o', 'racc': 'o', 'rac': 'c',
    'rada': 'e', 'rad': 'a', 'raffis': 'e', 'raffi': 's', 'rafflin': 'e', 'raffli': 'n', 'raffl': 'i', 'raff': 'l',
    'raf': 'f', 'ra': 'f', 'rb': 'e', 'r': 'b', 'sabbatica': 'e', 'sabbatic': 'a', 'sabbati': 'c', 'sabbat': 'i',
    'sabba': 't', 'sabb': 'a', 'sabe': 'e', 'sab': 'e', 'sacchari': 'e', 'sacchar': 'i', 'saccha': 'r', 'sacch': 'a',
    'sacc': 'h', 'sac': 'c', 'safar': 'e', 'safa': 'r', 'saffro': 'e', 'saffr': 'o', 'saff': 'r', 'saf': 'f',
    'sahar': 'e', 'saha': 'r', 'sah': 'a', 'sa': 'h', 'sb': 'e', 's': 'b', 'tachini': 'e', 'tachin': 'i', 'tachi': 'n',
    'tach': 'i', 'taci': 'e', 'tac': 'i', 'tadpol': 'e', 'tadpo': 'l', 'tadp': 'o', 'tad': 'p', 'taffet': 'e',
    'taffe': 't', 'taff': 'e', 'taf': 'f', 'tahit': 'e', 'tahi': 't', 'tah': 'i', 'ta': 'h', 'tb': 'e', 't': 'b',
    'ua': 'e', 'u': 'a', 'vacancie': 'e', 'vacanci': 'e', 'vacanc': 'i', 'vacan': 'c', 'vacatin': 'e', 'vacati': 'n',
    'vacat': 'i', 'vaca': 't', 'vaccinatin': 'e', 'vaccinati': 'n', 'vaccinato': 'e', 'vaccinat': 'o', 'vaccina': 't',
    'vaccin': 'a', 'vacci': 'n', 'vacc': 'i', 'vacillatin': 'e', 'vacillati': 'n', 'vacillat': 'i', 'vacilla': 't',
    'vacill': 'a', 'vacil': 'l', 'vaci': 'l', 'vac': 'i', 'vadu': 'e', 'vad': 'u', 'vagabon': 'e', 'vagabo': 'n',
    'vagab': 'o', 'vaga': 'b', 'vagin': 'e', 'vagi': 'n', 'vagranc': 'e', 'vagran': 'c', 'vagra': 'n', 'vagr': 'a',
    'vagu': 'e', 'vag': 'u', 'vai': 'e', 'va': 'i', 'vb': 'e', 'v': 'b', 'wafe': 'e', 'waf': 'e', 'wais': 'e',
    'wai': 's', 'wakin': 'e', 'waki': 'n', 'wak': 'i', 'wa': 'k', 'wb': 'e', 'w': 'b', 'xavie': 'e', 'xavi': 'e',
    'xav': 'i', 'xa': 'v', 'xb': 'e', 'x': 'b', 'yach': 'e', 'yac': 'h', 'yaho': 'e', 'yah': 'o', 'yalt': 'e',
    'yal': 't', 'yan': 'e', 'ya': 'n', 'yb': 'e', 'y': 'b', 'zabaglion': 'e', 'zabaglio': 'n', 'zabagli': 'o',
    'zabagl': 'i', 'zabag': 'l', 'zaba': 'g', 'zab': 'a', 'za': 'b', 'zb': 'e', 'z': 'b', '': 'a', 'abjectl': 'e',
    'adherenc': 'e', 'adheren': 'c', 'afa': 'e', 'af': 'a', 'agai': 'e', 'aga': 'i', 'agglomeratio': 'e',
    'agglomerati': 'o', 'agglomerat': 'i', 'agglomera': 't', 'agglomer': 'a', 'agglome': 'r', 'agglom': 'e',
    'agglo': 'm', 'agglutinat': 'e', 'agglutina': 't', 'agglutin': 'a', 'aggluti': 'n', 'agglut': 'i', 'agglu': 't',
    'aggl': 'o', 'agg': 'l', 'aghas': 'e', 'agha': 's', 'agh': 'a', 'ag': 'h', 'ahea': 'e', 'ahe': 'a', 'ahmadaba': 'e',
    'ahmadab': 'a', 'ahmada': 'b', 'ahmad': 'a', 'ahma': 'd', 'ahm': 'a', 'aho': 'e', 'ah': 'o', 'aisl': 'e',
    'ais': 'l', 'aitke': 'e', 'aitk': 'e', 'ait': 'k', 'ai': 't', 'aja': 'e', 'aj': 'a', 'akimb': 'e', 'akim': 'b',
    'aki': 'm', 'ak': 'i', 'alabamia': 'e', 'alabami': 'a', 'alabam': 'i', 'alaba': 'm', 'alab': 'a', 'ala': 'b',
    'albani': 'e', 'alban': 'i', 'albatros': 'e', 'albatro': 's', 'albatr': 'o', 'albat': 'r', 'alba': 'n', 'alb': 'a',
    'alcatra': 'e', 'alcatr': 'a', 'alcat': 'r', 'alca': 't', 'alchemis': 'e', 'alchemi': 's', 'alchem': 'i',
    'alche': 'm', 'alch': 'e', 'alc': 'h', 'alde': 'e', 'ald': 'e', 'alfalf': 'e', 'alfal': 'f', 'alfa': 'l',
    'alf': 'a', 'alga': 'e', 'alg': 'a', 'alhambr': 'e', 'alhamb': 'r', 'alham': 'b', 'alha': 'm', 'alh': 'a',
    'al': 'h', 'amadeu': 'e', 'amade': 'u', 'amad': 'e', 'ama': 'd', 'ambassado': 'e', 'ambassad': 'o', 'ambassa': 'd',
    'ambass': 'a', 'ambas': 's', 'amba': 's', 'ambe': 'e', 'amb': 'e', 'amebi': 'e', 'ameb': 'i', 'amelioratin': 'e',
    'ameliorati': 'n', 'ameliorato': 'e', 'ameliorat': 'o', 'ameliora': 't', 'amelior': 'a', 'amelio': 'r',
    'ameli': 'o', 'amel': 'i', 'ame': 'l', 'amhari': 'e', 'amhar': 'i', 'amha': 'r', 'amh': 'a', 'amiabilit': 'e',
    'amiabili': 't', 'amiabil': 'i', 'amiabi': 'l', 'amiabl': 'e', 'amiab': 'l', 'amia': 'b', 'ami': 'a', 'amma': 'e',
    'amm': 'a', 'amnesi': 'e', 'amnes': 'i', 'amne': 's', 'amn': 'e', 'amoeba': 'e', 'amoeb': 'a', 'amoe': 'b',
    'amo': 'e', 'amritsa': 'e', 'amrits': 'a', 'amrit': 's', 'amri': 't', 'amr': 'i', 'am': 'r', 'anabaptis': 'e',
    'anabapti': 's', 'anabapt': 'i', 'anabap': 't', 'anaba': 'p', 'anab': 'a', 'anachronisti': 'e', 'anachronist': 'i',
    'anachronis': 't', 'anachroni': 's', 'anachron': 'i', 'anachro': 'n', 'anachr': 'o', 'anach': 'r', 'anacond': 'e',
    'anacon': 'd', 'anaco': 'n', 'anac': 'o', 'anaesthetiz': 'e', 'anaestheti': 'z', 'anaesthet': 'i', 'anaesthe': 't',
    'anaesth': 'e', 'anaest': 'h', 'anaes': 't', 'anae': 's', 'anagra': 'e', 'anagr': 'a', 'anag': 'r', 'ana': 'g',
    'ancesto': 'e', 'ancest': 'o', 'ances': 't', 'ance': 's', 'anchovie': 'e', 'anchovi': 'e', 'anchov': 'i',
    'ancho': 'v', 'anch': 'o', 'anc': 'h', 'anecdota': 'e', 'anecdot': 'a', 'anecdo': 't', 'anecd': 'o', 'anec': 'd',
    'ane': 'c', 'ange': 'e', 'ang': 'e', 'anhydrid': 'e', 'anhydri': 'd', 'anhydrou': 'e', 'anhydro': 'u',
    'anhydr': 'i', 'anhyd': 'r', 'anhy': 'd', 'anh': 'y', 'anilin': 'e', 'anili': 'n', 'anil': 'i', 'ani': 'l',
    'ankar': 'e', 'anka': 'r', 'ankl': 'e', 'ank': 'l', 'anodi': 'e', 'anod': 'i', 'anoin': 'e', 'anoi': 'n',
    'anomalie': 'e', 'anomali': 'e', 'anomalou': 'e', 'anomalo': 'u', 'anomal': 'i', 'anoma': 'l', 'anomi': 'e',
    'anom': 'i', 'anora': 'e', 'anor': 'a', 'anothe': 'e', 'anoth': 'e', 'anot': 'h', 'ano': 't', 'answe': 'e',
    'answ': 'e', 'ans': 'w', 'an': 's', 'answerabl': 'e', 'answerab': 'l', 'answera': 'b', 'answere': 'e',
    'answerin': 'e', 'answeri': 'n', 'aorti': 'e', 'aort': 'i', 'aor': 't', 'ao': 'r', 'apach': 'e', 'apac': 'h',
    'apar': 'e', 'apa': 'r', 'aphasi': 'e', 'aphas': 'i', 'apha': 's', 'aph': 'a', 'apiec': 'e', 'apie': 'c',
    'apin': 'e', 'api': 'n', 'aplom': 'e', 'aplo': 'm', 'apl': 'o', 'ap': 'l', 'aqueduc': 'e', 'aquedu': 'c',
    'aqued': 'u', 'aque': 'd', 'aquife': 'e', 'aquif': 'e', 'aquilin': 'e', 'aquili': 'n', 'aquil': 'i', 'aqui': 'l',
    'aqu': 'e', 'aq': 'u', 'aquaplanin': 'e', 'aquaplani': 'n', 'aquaplan': 'i', 'aquapla': 'n', 'aquapl': 'a',
    'aquap': 'l', 'aquariu': 'e', 'aquari': 'u', 'aquar': 'i', 'aquati': 'e', 'aquat': 'i', 'arachni': 'e',
    'arachn': 'i', 'arach': 'n', 'arac': 'h', 'ara': 'c', 'ar': 'a', 'arabesqu': 'e', 'arabesq': 'u', 'arabes': 'q',
    'arabe': 's', 'arabi': 'e', 'arabl': 'e', 'asbesto': 'e', 'asbest': 'o', 'asbes': 't', 'asbe': 's', 'asb': 'e',
    'as': 'b', 'atavisti': 'e', 'atavist': 'i', 'atavis': 't', 'atavi': 's', 'atav': 'i', 'ata': 'v', 'atheis': 'e',
    'athei': 's', 'athenia': 'e', 'atheni': 'a', 'athen': 'i', 'athe': 'n', 'athirs': 'e', 'athir': 's', 'athi': 'r',
    'ath': 'i', 'atil': 'e', 'ati': 'l', 'atkin': 'e', 'atki': 'n', 'atk': 'i', 'at': 'k', 'atkinso': 'e', 'aubre': 'e',
    'aubr': 'e', 'aubur': 'e', 'aubu': 'r', 'aub': 'r', 'au': 'b', 'avai': 'e', 'ava': 'i', 'avengin': 'e',
    'avengi': 'n', 'aveng': 'i', 'aven': 'g', 'ave': 'n', 'av': 'e', 'avengefu': 'e', 'avengef': 'u', 'averagin': 'e',
    'averagi': 'n', 'averag': 'i', 'avera': 'g', 'averre': 'e', 'averr': 'e', 'aversel': 'e', 'aversio': 'e',
    'aversi': 'o', 'averte': 'e', 'avertin': 'e', 'averti': 'n', 'awai': 'e', 'awa': 'i', 'awfu': 'e', 'awf': 'u',
    'awhil': 'e', 'awhi': 'l', 'awh': 'i', 'aw': 'h', 'axe': 'e', 'ax': 'e', 'ay': 'e', 'azale': 'e', 'azal': 'e',
    'aza': 'l', 'az': 'a', 'ibide': 'e', 'oafis': 'e', 'oafi': 's', 'oaku': 'e', 'oarloc': 'e', 'oarlo': 'c',
    'oarl': 'o', 'oarsma': 'e', 'oarsm': 'a', 'oatcak': 'e', 'oatca': 'k', 'oatc': 'a', 'oatmea': 'e', 'oatme': 'a',
    'oatm': 'e'
}


def play(fragment):
    if fragment in moves:
        return moves[fragment]
    elif len(fragment) >= 3:
        return "challenge"
    else:
        print("qpwoeirut_agent: fragment missing in cache!")
        return "z"
