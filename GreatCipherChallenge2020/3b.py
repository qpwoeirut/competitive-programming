from gunnCryptoClub.polyalphabetic.vigenereCipher import decrypt
from gunnCryptoClub.englishDetection.englishScore import english_word_score as score


s = "Jjrboi, dvge jsmcgvwu cz xzv ktsdv oe xg dofxwig etaiwfysc htef ysd wajhqv gw hti kywqpv rbp xjzrqrl, icxpwu kuxz vloiwuwzk kdcaxzesew vfkz lacz, yeczbs tsgsd qgesk efu gbifuwzk ak. Izhwi hti ylwpefts aj zvf Oljzgfmse dmwlffe, wzv szxwihmmfvr tijjsxj, tvguhwj, kuxz jiol zlamrw rqtmwmsyifkg mw kvbfiftwzk s pcgxz kc tenv vuw zrbpw ulh ajx, ywe xgeugi lffz smk kuxz gwzgwig, mrv ywe fgum nyjesp edzjq, fwtogww ys tev ecf ofvsxiv ucir ae hti jrwz xg uc tsffid xg r ruvlp ddsuvgemge cr qgeye azzqt tsjgqh ozhtmf ywe zavk, mx s uwexseqq sx jcyi xztfc gi gublp mmvvj. Wf mk cwwidp szsmxv flsk, faslvr ur lys isgug aj Xiozgw rbp Rgikmc, lysdi ovfq kjfkury kfqik, nvqr lyof wmwtqvwi kmw hlh fs vvofl, scfqevp amvcvr nc lys Isguamr, Xrhq, xg tcyi vfkz efu pq wsnb urlf paejug, fs eryq e uvffeae aazsszq jjraqagiy imly o eeub ozh s bbujw zb ux, lvfdmtcs ur zzgfsjp. Wf mk cwwidp szsmxv flsk wz xzv fayyy cgxzfieik ft esev hupdvfe sx kvq lwrjk psere evaooifk ha Tsiwe, xzvfq awis elwchqvwu tdse kvq awrhtij kvmx nvfk hsp, fghw todxk, ssetskhqvwu kuxz iiexat auvw, jbgjxvr mfglh nc hzue, efu faskksp mf sm bsmchdc, oywol lys Rejdsd, Hwrht, lsu oxvwrrk wwk obejk ha fw ywe xmdpdmdj cr xzv Fqzgcifmge."

dec = decrypt("esrom", s)
print(score(dec))
print(dec)
print(len(dec.split()))